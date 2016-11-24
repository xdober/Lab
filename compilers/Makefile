all:
	bison -dv syntax.y
	flex lexical_cpy.l
	gcc -std=gnu99 -O2 -g -Wall -Wextra syntax.tab.c tree.c -o parser

.PHONY=run

run:
	./parser test.c
