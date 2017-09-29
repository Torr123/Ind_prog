# Makefile for Evgeniy_Onegin project

binary: Evgeniy_Onegin.o libevg.so
	gcc -o binary Evgeniy_Onegin.o -L. -levg -Wl,-rpath,.

Evgeniy_Onegin.o: Evgeniy_Onegin.c
	gcc -c Evgeniy_Onegin.c

libevg.so: Str.o File.o Cmp.o
	gcc -shared -o libevg.so Str.o File.o Cmp.o

Str.o: Str.c
	gcc -c -fPIC Str.c

File.o: File.c
	gcc -c -fPIC File.c

Cmp.o: Cmp.c
	gcc -c -fPIC Cmp.c

clean:
	rm -f *.o *.so binary Evgeniy_Onegin_BETTER.txt Evgeniy_Onegin_DA_BEST.txt
