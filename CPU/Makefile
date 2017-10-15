# Makefile for Evgeniy_Onegin project

cpu.exe: cpu_main.o libcpu.so libst.so
	gcc -o cpu.exe cpu_main.o -L. -lcpu -lst -lm -Wl,-rpath,.

cpu_main.o: cpu_main.c
	gcc -c cpu_main.c

libcpu.so: Cpu.o Cpu_Compeller.o
	gcc -shared -o libcpu.so Cpu.o Cpu_Compeller.o

Cpu.o: cpulib/Cpu.c
	gcc -c -fPIC cpulib/Cpu.c

Cpu_Compeller.o: cpulib/Cpu_Compeller.c
	gcc -c -fPIC cpulib/Cpu_Compeller.c

libst.so: Stack.o Hash.o Input.o
	gcc -shared -o libst.so Stack.o Hash.o Input.o

Stack.o: stacklib/Stack.c
	gcc -c -fPIC stacklib/Stack.c

Hash.o: stacklib/Hash.c
	gcc -c -fPIC stacklib/Hash.c

Input.o: stacklib/Input.c
	gcc -c -fPIC stacklib/Input.c

clean:
	rm -f *.o *.so cpu.exe cpu_a.out
