#define HOOK(_name, _function, _original)  \  
    {                                      \
        .name = (_name),                   \
        .function = (_function),           \
        .original = (_original),           \
    }

/* массив перехватываемых функций */
static struct ftrace_hook demo_hooks[] = {
    HOOK("__x64_sys_clone",  hook_sys_clone,  &orig_sys_clone),
    HOOK("__x64_sys_execve", hook_sys_execve, &orig_sys_execve),
    HOOK("bdev_read_page", hook_bdev_read_page, &orig_bdev_read_page),
    HOOK("bdev_write_page", hook_bdev_write_page, &orig_bdev_write_page),
};
