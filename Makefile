all:
	bison -H parse.y
	flex c.l
	gcc parse.tab.c
clean:
	-rm *.yy.c *.tab.h *.tab.c a.out
