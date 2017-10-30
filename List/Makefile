#Makefile for list project

list.exe: list_main.o liblist.so
	gcc -o list.exe list_main.o -L. -llist -Wl,-rpath,.

list_main.o: list_main.c
	gcc -c list_main.c

liblist.so: List.o
	gcc -shared -o liblist.so List.o

List.o: listlib/List.c
	gcc -c -fPIC listlib/List.c

clean:
	rm -f *.exe *.o *.so List_Dump
