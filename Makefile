all:
	gcc cpu_i386_init_no_copr.c instr.c -o cpu_i386
clean:
	rm -f cpu_i386
