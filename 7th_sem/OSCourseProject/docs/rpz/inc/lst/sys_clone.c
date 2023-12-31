static asmlinkage long (*orig_sys_clone)(unsigned long clone_flags,
		unsigned long newsp, int __user *parent_tidptr,
		int __user *child_tidptr, unsigned long tls);

static asmlinkage long hook_sys_clone(unsigned long clone_flags,
		unsigned long newsp, int __user *parent_tidptr,
		int __user *child_tidptr, unsigned long tls)
{
	long ret = orig_sys_clone(clone_flags, newsp, parent_tidptr,
		child_tidptr, tls);
	pr_info("clone(): %ld\n", ret);

	return ret;
}