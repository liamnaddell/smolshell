all:
	bison -H parse.y
	flex c.l
	gcc parse.tab.c
