#Makefile for tree project

prog_lang.exe: prog_lang.o libtree.so libCStr_To_Tr.so
	gcc -o prog_lang.exe prog_lang.o -L. -ltree -lCStr_To_Tr -lm -Wl,-rpath,.

prog_lang.o: prog_lang.c
	gcc -c prog_lang.c

libtree.so: Tree.o
	gcc -shared -o libtree.so Tree.o

libCStr_To_Tr.so: CString_To_Tree.o
	gcc -shared -o libCStr_To_Tr.so CString_To_Tree.o

CString_To_Tree.o: CString_To_Tree.c
	gcc -c -fPIC CString_To_Tree.c

Tree.o: Tree.c
	gcc -c -fPIC Tree.c

dot: Tree_Out.dot
	dot -Tjpg -O Tree_Out.dot
	xdg-open Tree_Out.dot.jpg

clean:
	rm *.o *.so *.exe *.dot *.jpg Code.my_cpu

cpy:
	cp Code.my_cpu ../CPU/assembly
