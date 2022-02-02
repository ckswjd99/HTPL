%{
#include "htpl.h"
#include "htpl.tab.h"

int yylex ();
int yyerror (char* s);

int yaccDebug = 0;

%}

%union {
    int     intVal;
    char*   stringVal;
    attrNode* attrNodePtr;
}

%type<attrNodePtr> attribute attribute_list

%left BIGGER LESS SAME PLUS MINUS MULT DIVIDE
%left OR AND
%right NOT

%token COMMONTAG_OPEN_START COMMONTAG_CLOSE_START SINGLETAG_START SINGLETAG_END TAG_END
%token DOCTYPE_TAG
%token<stringVal> HTML HEAD BODY
%token<intVal> NUMBER_CONST
%token<stringVal> TAG_NAME ATTR_NAME ATTR_VAL STRING

%%
program: DOCTYPE_TAG structure

structure: html_open head body html_close

html_open: COMMONTAG_OPEN_START HTML attribute_list TAG_END {
    pushTagStack($2, $3);
    if(yaccDebug) printf("push tag %s, %d attributes\n", $2, getAttrListLen($3));
}
html_close: COMMONTAG_CLOSE_START HTML TAG_END {
    tagNode* temp = popTagStack();
    if(yaccDebug) printf("pop tag %s\n", temp->name);
    freeTagNode(temp);
}

head: head_open innerHTML head_close
head_open: COMMONTAG_OPEN_START HEAD attribute_list TAG_END {
    pushTagStack($2, $3);
    if(yaccDebug) printf("push tag %s, %d attributes\n", $2, getAttrListLen($3));
}
head_close: COMMONTAG_CLOSE_START HEAD TAG_END {
    tagNode* temp = popTagStack();
    if(yaccDebug) printf("pop tag %s\n", temp->name);
    freeTagNode(temp);
}

body: body_open innerHTML body_close 
body_open: COMMONTAG_OPEN_START BODY attribute_list TAG_END {
    pushTagStack($2, $3);
    if(yaccDebug) printf("push tag %s, %d attributes\n", $2, getAttrListLen($3));
}
body_close: COMMONTAG_CLOSE_START BODY TAG_END {
    tagNode* temp = popTagStack();
    if(yaccDebug) printf("pop tag %s\n", temp->name);
    freeTagNode(temp);
}

attribute_list
    : attribute attribute_list {
        $1->next = $2;
        $$ = $1;
    }
    | /* empty */ {
        $$ = NULL;
    }

attribute: ATTR_NAME '=' ATTR_VAL {
    attrElement* temp = (attrElement*)malloc(sizeof(attrElement));
    temp->name = strdup($1);
    temp->value = strdup($3);
    
    attrNode* tempNode = (attrNode*)malloc(sizeof(attrNode));
    tempNode->next = NULL;
    tempNode->data = temp;

    $$ = tempNode;
}

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
common_tag_open: COMMONTAG_OPEN_START TAG_NAME attribute_list TAG_END {
    pushTagStack($2, $3);
    if(yaccDebug) printf("push tag %s, %d attributes\n", $2, getAttrListLen($3));
}
common_tag_close: COMMONTAG_CLOSE_START TAG_NAME TAG_END {
    tagNode* temp = popTagStack();
    if(yaccDebug) {
        printf("pop tag %s, ", temp->name);
        printAttrList(temp->attr);
    }

    // tag parenthesis check
    if(strcmp(temp->name, $2) != 0) {
        printError("tag accordance: %s expected, got %s\n", temp->name, $2);
    }

    freeTagNode(temp);
}

single_tag: SINGLETAG_START TAG_NAME attribute_list SINGLETAG_END

expr
    : or_expr

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
    | unary

unary
    : NUMBER_CONST
    | STRING
    | single_tag
    | common_tag
    | MINUS unary
    | NOT unary %prec MULT

%%

/* Additional C Codes */
int    yyerror (char* s) {
	fprintf (stderr, "%s\n", s);
}

void printError(char* format, ...) {
    char buf[512] = {0,};
    va_list ap;

    va_start(ap, format);
    vsprintf(buf, format, ap);
    va_end(ap);

	if(!errorMute) printf("%s:%d: error:%s\n", filename, getLineNum(), buf);
}