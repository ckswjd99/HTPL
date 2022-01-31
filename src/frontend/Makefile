htpl: lex.yy.o hash.o
	gcc -o htpl lex.yy.o hash.o -lfl

lex.yy.o: lex.yy.c
	gcc -c -g lex.yy.c

lex.yy.c: htpl.l
	flex htpl.l

hash.o: hash.c htpl.h
	gcc -c -g hash.c

clean:
	rm lex.yy.c -f
	rm *.o -f
	rm htpl -f
