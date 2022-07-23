all:
	bison -H parse.y
	flex c.l
	gcc -ggdb parse.tab.c main.c parsetree.c
clean:
	-rm *.yy.c *.tab.h *.tab.c a.out
