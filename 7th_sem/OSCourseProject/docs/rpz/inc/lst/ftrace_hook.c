struct ftrace_hook {
	const char *name; 		// имя перехватываемой функции
	void *function;   		// адрес функции-обертки, вызываемой вместо перехваченной функции
	void *original; 		// указатель на мест, куда будет записан адрес перехватываемой функции

	unsigned long address; 	// адрес перехватываемой функции
	struct ftrace_ops ops;
};
