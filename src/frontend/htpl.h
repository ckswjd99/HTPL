#ifndef __HTPL_H__
#define __HTPL_H__

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// VALUE TYPE
#define _NUMBER 0
#define _TEXT 1


int errorMute;
int getLineNum();
char* filename;
void printError(char* format, ...);

typedef struct decl {
    char* name;
    char type;
    char number;
    char* text;
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

void freeTagNode(tagNode* node);

#endif