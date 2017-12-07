#Makefile for tree project

diff_main.exe: diff_main.o libtree.so
	gcc -o diff_main.exe diff_main.o -L. -ltree -lm -Wl,-rpath,.

diff_main.o: diff_main.c
	gcc -c diff_main.c

libtree.so: Tree.o
	gcc -shared -o libtree.so Tree.o

Tree.o: Tree.c
	gcc -c -fPIC Tree.c

dot: Tree_Out.dot
	dot -Tjpg -O Tree_Out.dot
	xdg-open Tree_Out.dot.jpg

clean:
	rm *.o *.so *.exe *.dot *.jpg
