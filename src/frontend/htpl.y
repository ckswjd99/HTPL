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
    tagNode* tagNodePtr;
    value*  valuePtr;
}

%type<attrNodePtr> attribute attribute_list
%type<tagNodePtr> html_open html_close head_open head_close body_open common_tag_open
%type<valuePtr> innerHTML clause_list clause common_tag single_tag body structure program
%type<valuePtr> body_close common_tag_close
%type<valuePtr> expr or_expr or_list and_expr and_list binary unary

%left BIGGER LESS SAME PLUS MINUS MULT DIVIDE
%left OR AND
%right NOT

%token COMMONTAG_OPEN_START COMMONTAG_CLOSE_START SINGLETAG_START SINGLETAG_END TAG_END
%token DOCTYPE_TAG
%token<stringVal> HTML HEAD BODY
%token<intVal> NUMBER_CONST
%token<stringVal> TAG_NAME ATTR_NAME ATTR_VAL STRING

%%
program: DOCTYPE_TAG structure { $$ = $2; }

structure: html_open head body html_close { $$ = $3; }

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

body: body_open innerHTML body_close { $$ = $3; }
body_open: COMMONTAG_OPEN_START BODY attribute_list TAG_END {
    if(yaccDebug) printf("push tag %s, %d attributes\n", $2, getAttrListLen($3));

    pushTagStack($2, $3);
    $$ = getTagStackTop();

    commonTagOpenHandler($$);
}
body_close: COMMONTAG_CLOSE_START BODY TAG_END {
    tagNode* temp = popTagStack();
    if(yaccDebug) printf("pop tag %s\n", temp->name);
    $$ = commonTagCloseHandler(temp);

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
    : clause_list { $$ = $1; }
    | expr { $$ = $1; }

clause_list
    : clause clause_list {
        $$ = $2 == NULL ? $1 : $2;
    }
    | /* empty */ {
        $$ = NULL;
    }

clause
    : common_tag { $$ = $1; }
    | single_tag { $$ = $1; }

common_tag: common_tag_open innerHTML common_tag_close { $$ = $3; }
common_tag_open: COMMONTAG_OPEN_START TAG_NAME attribute_list TAG_END {
    if(yaccDebug) printf("push tag %s, %d attributes\n", $2, getAttrListLen($3));

    pushTagStack($2, $3);
    $$ = getTagStackTop();

    commonTagOpenHandler($$);
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

    $$ = commonTagCloseHandler(temp);

    freeTagNode(temp);
}

single_tag: SINGLETAG_START TAG_NAME attribute_list SINGLETAG_END {
    $$ = singleTagHandler($2, $3);
}

expr
    : or_expr { $$ = $1; }

or_expr
    : or_list { $$ = $1; }

or_list
    : or_list OR and_expr { $$ = valueOR($1, $3); }
    | and_expr { $$ = $1; }

and_expr
    : and_list { $$ = $1; }

and_list
    : and_list AND binary { $$ = valueAND($1, $3); }
    | binary { $$ = $1; }

binary
    : binary BIGGER binary { $$ = valueComp($1, $3, _BIGGER); }
    | binary LESS binary { $$ = valueComp($1, $3, _LESS); }
    | binary SAME binary { $$ = valueComp($1, $3, _SAME); }
    | binary PLUS binary { $$ = valueBinOp($1, $3, _PLUS); }
    | binary MINUS binary { $$ = valueBinOp($1, $3, _MINUS); }
    | binary MULT binary { $$ = valueBinOp($1, $3, _MULT); }
    | binary DIVIDE binary { $$ = valueBinOp($1, $3, _DIVIDE); }
    | unary { $$ = $1; }

unary
    : NUMBER_CONST { $$ = parseNumber($1); }
    | STRING { $$ = parseText($1); }
    | single_tag { $$ = $1; }
    | common_tag { $$ = $1; }
    | MINUS unary { $$ = valueNEG($2); }
    | NOT unary %prec MULT { $$ = valueNOT($2); }

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