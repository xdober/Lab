all:
	bison -dv syntax.y
	flex lexical.l
	gcc -g syntax.tab.c tree.c lex.yy.c -lfl -ly -o parser

.PHONY=run debug

run:
	./parser test1.cmn

debug:
	gdb parser -ex "r test1.cmn"
