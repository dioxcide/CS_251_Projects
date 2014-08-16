project5.exe: tst.o bst.o
	gcc -o project5.exe tst.o bst.o
tst.o: tst.c bst.h
	gcc -c tst.c
bst.o: bst.c bst.h
	gcc -c bst.c
rm: clean tst.o bst.o
