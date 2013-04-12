all :
	bison -d -v draw.y
	lex draw.l
	gcc draw.tab.c lex.yy.c draw.c -lfl -lm -o draw