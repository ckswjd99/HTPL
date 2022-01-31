#
# This is a makefile for the skeleton program for project 2.
#

CC = gcc
LEX = flex
YACC = bison
COMPILE_OPTION = -g
LINK_OPTION = -lfl
YACC_OPTION = -vd

all : htpl

clean :
	rm -f *.o lex.yy.c htpl.tab.c htpl.tab.h htpl.output htpl htpl_lexer

htpl : lex.yy.o hash.o htpl.tab.o
	${CC} -o htpl lex.yy.o hash.o htpl.tab.o ${LINK_OPTION}

htpl.tab.o : htpl.tab.c htpl.h
	${CC} -c ${COMPILE_OPTION} htpl.tab.c

hash.o : hash.c htpl.h
	${CC} -c ${COMPILE_OPTION} hash.c

lex.yy.o : lex.yy.c htpl.tab.h htpl.h
	${CC} -c ${COMPILE_OPTION} lex.yy.c

lex.yy.c : htpl.l
	${LEX} htpl.l

htpl.tab.h htpl.tab.c : htpl.y
	${YACC} ${YACC_OPTION} htpl.y

lexer: hash.o
	${LEX} htpl.l
	${CC} -c lex.yy.c
	${CC} -o htpl_lexer lex.yy.o hash.o -lfl
