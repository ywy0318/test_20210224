all:
	gcc memory_leak_OOM.c -o memory_leak_OOM -g
	env MALLOC_TRACE=memory_leak_OOM.log ./memory_leak_OOM
	mtrace memory_leak_OOM memory_leak_OOM.log