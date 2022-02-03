#ifndef __HTPL_H__
#define __HTPL_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// VALUE TYPE
#define _NUMBER 0
#define _TEXT 1

// OPERATION TYPE
#define _BIGGER 0
#define _LESS 1
#define _SAME 2
#define _PLUS 3
#define _MINUS 4
#define _MULT 5
#define _DIVIDE 6


int errorMute;
int getLineNum();
char* filename;
void printError(char* format, ...);

typedef struct value {
    char type;
    char number;
    char* text;
} value;

typedef struct decl {
    char* name;
    value* value;
} decl;

/* ATTRIBUTE HANDLER */
typedef struct attrElement {
    char* name;
    char* value;
} attrElement;

typedef struct attrNode {
    struct attrNode* next;
    attrElement* data;
} attrNode;

void freeAttrList(attrNode* list);
int getAttrListLen(attrNode* list);
void printAttrList(attrNode* list);

/* TAG STACK */
typedef struct tagNode {
    struct tagNode *next;
    char* name;
    attrNode* attr;
} tagNode;

tagNode* tagStack;
tagNode* tagStackTop;
void initTagStack();
void pushTagStack(char* name, attrNode* attr);
tagNode* popTagStack();
tagNode* getTagStackTop();

void freeTagNode(tagNode* node);


/* TAG HANDLER */
void commonTagOpenHandler(tagNode* openTag);
value* commonTagCloseHandler(tagNode* closeTag);
value* singleTagHandler(char* tagName, attrNode* attrList);


/* VALUE OPERATION */
value* valueNEG(value* v1);
value* valueNOT(value* v1);
value* valueOR(value* v1, value* v2);
value* valueAND(value* v1, value* v2);
value* valueComp(value* v1, value* v2, int type);
value* valueBinOp(value* v1, value* v2, int type);

value* parseNumber(int raw);
value* parseText(char* raw);

#endif