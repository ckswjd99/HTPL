%{
#include "htpl.h"
#include "htpl.tab.h"

int    yylex ();
int    yyerror (char* s);
%}

%union {
    int     intVal;
    char*   stringVal;
}

%token COMMONTAG_OPEN_START COMMONTAG_CLOSE_START SINGLETAG_START SINGLETAG_END TAG_END
%token DOCTYPE_TAG HTML HEAD BODY P
%token OR AND NOT
%token BIGGER LESS SAME PLUS MINUS MULT DIVIDE
%token NUMBER_CONST
%token<stringVal> TAG_NAME ATTRIBUTE_NAME ATTRIBUTE_VAL STRING

%%
program: DOCTYPE_TAG structure

structure: html_open head body html_close

html_open: COMMONTAG_OPEN_START HTML attribute_list TAG_END
html_close: COMMONTAG_CLOSE_START HTML TAG_END

head: head_open innerHTML head_close
head_open: COMMONTAG_OPEN_START HEAD attribute_list TAG_END
head_close: COMMONTAG_CLOSE_START HEAD TAG_END

body: body_open innerHTML body_close
body_open: COMMONTAG_OPEN_START BODY attribute_list TAG_END
body_close: COMMONTAG_CLOSE_START BODY TAG_END

attribute_list
    : attribute attribute_list
    | /* empty */

attribute: ATTRIBUTE_NAME '=' ATTRIBUTE_VAL

innerHTML
    : clause_list
    | expr

clause_list
    : clause clause_list
    | /* empty */

clause
    : common_tag
    | single_tag

common_tag: common_tag_open innerHTML common_tag_close
common_tag_open: COMMONTAG_OPEN_START TAG_NAME attribute_list TAG_END
common_tag_close: COMMONTAG_CLOSE_START TAG_NAME TAG_END

single_tag: SINGLETAG_START TAG_NAME attribute_list SINGLETAG_END

expr
    : /* empty */
    | unary
    | or_expr

or_expr
    : or_list

or_list
    : or_list OR and_expr
    | and_expr

and_expr
    : and_list

and_list
    : and_list AND binary
    | binary

binary
    : binary BIGGER binary
    | binary LESS binary
    | binary SAME binary
    | binary PLUS binary
    | binary MINUS binary
    | binary MULT binary
    | binary DIVIDE binary

unary
    : p_open expr p_close
    | p_open unary p_close
    | NUMBER_CONST
    | STRING
    | single_tag
    | MINUS unary
    | NOT unary

p_open: COMMONTAG_OPEN_START P attribute_list TAG_END
p_close: COMMONTAG_CLOSE_START P TAG_END

%%

/* Additional C Codes */
int    yyerror (char* s)
{
	fprintf (stderr, "%s\n", s);
}