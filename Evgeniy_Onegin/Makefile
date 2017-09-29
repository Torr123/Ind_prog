# Makefile for Evgeniy_Onegin project

evgen.exe: Evgeniy_Onegin.o libevg.so
	gcc -o evgen.exe Evgeniy_Onegin.o -L. -levg -Wl,-rpath,.

Evgeniy_Onegin.o: Evgeniy_Onegin.c
	gcc -c Evgeniy_Onegin.c

libevg.so: Str.o File.o Cmp.o
	gcc -shared -o libevg.so Str.o File.o Cmp.o

Str.o: lib/Str.c
	gcc -c -fPIC lib/Str.c

File.o: lib/File.c
	gcc -c -fPIC lib/File.c

Cmp.o: lib/Cmp.c
	gcc -c -fPIC lib/Cmp.c

clean:
	rm -f *.o *.so evgen.exe Evgeniy_Onegin_BETTER.txt Evgeniy_Onegin_DA_REVERCE.txt
