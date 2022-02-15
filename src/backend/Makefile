#
# This is a makefile for the skeleton program for project 3.
#

CC = gcc
LEX = flex
YACC = bison
COMPILE_OPTION = -g
LINK_OPTION = -lfl
YACC_OPTION = -vd

all : htpl

clean :
	rm -f *.o lex.yy.c htpl.tab.c htpl.tab.h htpl.output htpl htpl.exe

htpl : lex.yy.o htpl.o htpl.tab.o
	${CC} -o htpl lex.yy.o htpl.o htpl.tab.o ${LINK_OPTION}

htpl.o : 
	${CC} -c ${COMPILE_OPTION} htpl.c -o htpl.o

htpl.tab.o : htpl.tab.c htpl.h
	${CC} -c ${COMPILE_OPTION} htpl.tab.c

lex.yy.o : lex.yy.c htpl.tab.h htpl.h
	${CC} -c ${COMPILE_OPTION} lex.yy.c

lex.yy.c : htpl.l
	${LEX} htpl.l

htpl.tab.h htpl.tab.c : htpl.y
	${YACC} ${YACC_OPTION} htpl.y
