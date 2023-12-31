static asmlinkage long (*orig_sys_execve)(const char __user *filename,
		const char __user *const __user *argv,
		const char __user *const __user *envp);

static asmlinkage long hook_sys_execve(const char __user *filename,
		const char __user *const __user *argv,
		const char __user *const __user *envp)
{
	long ret;
	char *kernel_filename;

	kernel_filename = duplicate_filename(filename);
	kfree(kernel_filename);
	ret = orig_sys_execve(filename, argv, envp);
	pr_info("execve(): %ld\n", ret);

	return ret;
}