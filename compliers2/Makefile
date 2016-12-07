all:
	bison -dv syntax.y
	flex lexical.l
	gcc -g syntax.tab.c tree.c lex.yy.c -lfl -ly -o parser

.PHONY=run debug

run:
	./parser test1.c
	./parser test2.c
	./parser test3.c
	./parser test4.c
	./parser test5.c
	./parser test6.c
	./parser test7.c
	./parser test8.c
	./parser test9.c
	./parser test10.c
	./parser test11.c
	./parser test12.c
	./parser test13.c
	./parser test14.c
	./parser test15.c
	./parser test16.c
	./parser test17.c

debug:
	gdb parser -ex "r test1.c"
