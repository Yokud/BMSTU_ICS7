#define pr_fmt(fmt) "hook_functions: " fmt

#include <linux/init.h>
#include <linux/ftrace.h>
#include <linux/kallsyms.h>
#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/version.h>
#include <linux/syscalls.h>

MODULE_DESCRIPTION("System calls and block devices operations monitoring module");
MODULE_AUTHOR("Malyshev Ivan");
MODULE_LICENSE("GPL");

#define USE_FENTRY_OFFSET 0

/* struct ftrace_hook описывает перехватываемую функцию
name - имя перехватываемой функции
function - адрес функции-обертки, вызываемой вместо перехваченной функции
original - указатель на мест, куда будет записан адрес перехватываемой функции
address - адрес перехватываемой функции
*/
struct ftrace_hook {
	const char *name;
	void *function;
	void *original;

	unsigned long address;
	struct ftrace_ops ops;
};

/* адрес перехватываемой функции */
static int resolve_hook_address(struct ftrace_hook *hook)
{
	hook->address = kallsyms_lookup_name(hook->name);

	if (!hook->address) {
		pr_debug("unresolved symbol: %s\n", hook->name);
		return -ENOENT;
	}

#if USE_FENTRY_OFFSET
	*((unsigned long*) hook->original) = hook->address + MCOUNT_INSN_SIZE;
#else
	*((unsigned long*) hook->original) = hook->address;
#endif

	return 0;
}

/* выполнение перехвата функций */
static void notrace fh_ftrace_thunk(unsigned long ip, unsigned long parent_ip,
		struct ftrace_ops *ops, struct ftrace_regs *fregs)
{
    struct pt_regs *regs = ftrace_get_regs(fregs);

    /* получаем адрес struct ftrace_hook по адресу внедренной в неё struct ftrace_ops */
	struct ftrace_hook *hook = container_of(ops, struct ftrace_hook, ops);

#if USE_FENTRY_OFFSET
	regs->ip = (unsigned long) hook->function;
#else
    /* пропускаем вызовы функции из текущего модуля */
	if (!within_module(parent_ip, THIS_MODULE))
		regs->ip = (unsigned long) hook->function;
#endif
}

/* инициализация структуры ftrace_ops */
int install_hook(struct ftrace_hook *hook)
{
	int err;

	err = resolve_hook_address(hook);
	if (err)
		return err;

	hook->ops.func = fh_ftrace_thunk;
	hook->ops.flags = FTRACE_OPS_FL_SAVE_REGS
	                | FTRACE_OPS_FL_RECURSION
	                | FTRACE_OPS_FL_IPMODIFY;

    /* включить ftrace для функции */
	err = ftrace_set_filter_ip(&hook->ops, hook->address, 0, 0);
	if (err) {
		pr_debug("ftrace_set_filter_ip() failed: %d\n", err);
		return err;
	}

    /* разрешить ftrace вызывать коллбек */
	err = register_ftrace_function(&hook->ops);
	if (err) {
		pr_debug("register_ftrace_function() failed: %d\n", err);
		ftrace_set_filter_ip(&hook->ops, hook->address, 1, 0);
		return err;
	}

	return 0;
}

/* выключить перехват */
void remove_hook(struct ftrace_hook *hook)
{
	int err;

	err = unregister_ftrace_function(&hook->ops);
	if (err) {
		pr_debug("unregister_ftrace_function() failed: %d\n", err);
	}

	err = ftrace_set_filter_ip(&hook->ops, hook->address, 1, 0);
	if (err) {
		pr_debug("ftrace_set_filter_ip() failed: %d\n", err);
	}
}

int install_hooks(struct ftrace_hook *hooks, size_t count)
{
	int err;
	size_t i;

	for (i = 0; i < count; i++) {
		err = install_hook(&hooks[i]);
		if (err)
			goto error;
	}

	return 0;

error:
	while (i != 0) {
		remove_hook(&hooks[--i]);
	}

	return err;
}

void remove_hooks(struct ftrace_hook *hooks, size_t count)
{
	size_t i;

	for (i = 0; i < count; i++)
		remove_hook(&hooks[i]);
}

#ifndef CONFIG_X86_64
#error Currently only x86_64 architecture is supported
#endif

#if defined(CONFIG_X86_64) && (LINUX_VERSION_CODE >= KERNEL_VERSION(4,17,0))
#define PTREGS_SYSCALL_STUBS 1
#endif

#if !USE_FENTRY_OFFSET
#pragma GCC optimize("-fno-optimize-sibling-calls")
#endif

static asmlinkage long (*orig_sys_clone)(unsigned long clone_flags,
		unsigned long newsp, int __user *parent_tidptr,
		int __user *child_tidptr, unsigned long tls);

static asmlinkage long hook_sys_clone(unsigned long clone_flags,
		unsigned long newsp, int __user *parent_tidptr,
		int __user *child_tidptr, unsigned long tls)
{
	long ret;

	//pr_info("clone() before\n");

	ret = orig_sys_clone(clone_flags, newsp, parent_tidptr,
		child_tidptr, tls);

	pr_info("clone(): %ld\n", ret);

	return ret;
}

static char *duplicate_filename(const char __user *filename)
{
	char *kernel_filename;

	kernel_filename = kmalloc(4096, GFP_KERNEL);
	if (!kernel_filename)
		return NULL;

	if (strncpy_from_user(kernel_filename, filename, 4096) < 0) {
		kfree(kernel_filename);
		return NULL;
	}

	return kernel_filename;
}


/* Указатель на оригинальный обработчки системного вызова execve
Можно вызывать из обертки
*/
static asmlinkage long (*orig_sys_execve)(const char __user *filename,
		const char __user *const __user *argv,
		const char __user *const __user *envp);

/* Функция, которая будет вызываться вместо перехваченной
 Возвращаемое значение будет передано вызывающей функции
*/
static asmlinkage long hook_sys_execve(const char __user *filename,
		const char __user *const __user *argv,
		const char __user *const __user *envp)
{
	long ret;
	char *kernel_filename;

	kernel_filename = duplicate_filename(filename);

	//pr_info("execve() before: %s\n", kernel_filename);

	kfree(kernel_filename);

	ret = orig_sys_execve(filename, argv, envp);

	pr_info("execve(): %ld\n", ret);

	return ret;
}

static asmlinkage int (*orig_bdev_read_page)(struct block_device *bdev, sector_t sector, 
struct page *page);

static asmlinkage int hook_bdev_read_page(struct block_device *bdev, sector_t sector, 
	struct page *page)
{
    int res;

    res = orig_bdev_read_page(bdev, sector, page);
    pr_info("read page: from /dev/sda");

    return res;
}

static asmlinkage int (*orig_bdev_write_page)(struct block_device *bdev, sector_t sector, 
struct page *page, struct writeback_control **wc);


static asmlinkage int hook_bdev_write_page(struct block_device *bdev, sector_t sector, 
struct page *page, struct writeback_control **wc)
{
    int res;

    res = orig_bdev_write_page(bdev, sector, page, wc);
    pr_info("write page: to /dev/sda");

    return res;
}

#ifdef PTREGS_SYSCALL_STUBS
#define SYSCALL_NAME(name) ("__x64_" name)
#else
#define SYSCALL_NAME(name) (name)
#endif

#define HOOK(_name, _function, _original)    \
    {                    \
        .name = (_name),    \
        .function = (_function),    \
        .original = (_original),    \
    }

/* массив перехватываемых функций */
static struct ftrace_hook demo_hooks[] = {
    HOOK("__x64_sys_clone",  hook_sys_clone,  &orig_sys_clone),
    HOOK("__x64_sys_execve", hook_sys_execve, &orig_sys_execve),
    HOOK("bdev_read_page", hook_bdev_read_page, &orig_bdev_read_page),
    HOOK("bdev_write_page", hook_bdev_write_page, &orig_bdev_write_page),
};


static int __init hook_module_init(void)
{
	int err;

	err = install_hooks(demo_hooks, ARRAY_SIZE(demo_hooks));
	if (err)
		return err;

	pr_info("module loaded\n");

	return 0;
}

static void __exit hook_module_exit(void)
{
	remove_hooks(demo_hooks, ARRAY_SIZE(demo_hooks));
	pr_info("module unloaded\n");
}

module_init(hook_module_init);
module_exit(hook_module_exit);
