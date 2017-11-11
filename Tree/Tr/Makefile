#Makefile for tree project

tree_main.exe: tree_main.o libtree.so
	gcc -o tree_main.exe tree_main.o -L. -ltree -lm -Wl,-rpath,.

tree_main.o: tree_main.c
	gcc -c tree_main.c

libtree.so: Tree.o
	gcc -shared -o libtree.so Tree.o

Tree.o: Tree.c
	gcc -c -fPIC Tree.c

clean:
	rm *.o *.so *.exe
