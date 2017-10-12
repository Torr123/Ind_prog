# Makefile for Evgeniy_Onegin project

stk.exe: Stack_main.o libst.so
	gcc -o stk.exe Stack_main.o -L. -lst -Wl,-rpath,.

Stack_main.o: Stack_main.c
	gcc -c Stack_main.c

libst.so: Stack.o Input.o Hash.o
	gcc -shared -o libst.so Stack.o Input.o Hash.o

Stack.o: lib/Stack.c
	gcc -c -fPIC lib/Stack.c

Input.o: lib/Input.c
	gcc -c -fPIC lib/Input.c

Hash.o: lib/Hash.c
	gcc -c -fPIC lib/Hash.c

clean:
	rm -f *.o *.so stk.exe
