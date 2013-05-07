all :
	bison --report=all -d -v draw.y
	lex --yylineno draw.l
	gcc pile_variables.c tableaux_variables.c chemin.c  draw.tab.c lex.yy.c draw.c -lfl -lm -o draw