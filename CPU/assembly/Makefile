# Makefile for CPU project

compeller.exe: Cpu_Compeller.o libst.so libcomp.so
	gcc -o compeller.exe Cpu_Compeller.o -L. -lst -lcomp -lm -Wl,-rpath,.

Cpu_Compeller.o: Cpu_Compeller.c
	gcc -c Cpu_Compeller.c

libcomp.so: Compeller.o
	gcc -shared -o libcomp.so Compeller.o

Compeller.o: complib/Compeller.c
	gcc -c -fPIC complib/Compeller.c

libst.so: Stack.o Hash.o Input.o
	gcc -shared -o libst.so Stack.o Hash.o Input.o

Stack.o: ../stacklib/Stack.c
	gcc -c -fPIC ../stacklib/Stack.c

Hash.o: ../stacklib/Hash.c
	gcc -c -fPIC ../stacklib/Hash.c

Input.o: ../stacklib/Input.c
	gcc -c -fPIC ../stacklib/Input.c

clean:
	rm -f *.o *.so *exe

cpy:
	cp Binfile.mycpu ../cpu/
