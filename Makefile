all:
	gcc cpu_i386.c instr.c -o cpu_i386
clean:
	rm -f cpu_i386
