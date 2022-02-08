#include "../htpl.h"

/* TAG STACK */
void initTagStack() {
    tagStack = (tagNode*)malloc(sizeof(tagNode));
    tagStack->next = NULL;
    tagStack->name = NULL;
    tagStackTop = tagStack;
}

void pushTagStack(char* name, attrNode* attr) {
    tagNode* temp = (tagNode*)malloc(sizeof(tagNode));
    temp->next = NULL;
    temp->name = strdup(name);
    temp->attr = attr;
    
    tagStackTop->next = temp;
    tagStackTop = tagStackTop->next;
}

tagNode* popTagStack() {
    tagNode* newStackTop = tagStack;
    tagNode* oldStackTop;
    while(newStackTop->next != tagStackTop) newStackTop = newStackTop->next;
    
    oldStackTop = tagStackTop;
    tagStackTop = newStackTop;
    tagStackTop->next = NULL;

    return oldStackTop;
}

tagNode* getTagStackTop() {
    return tagStackTop;
}

void freeTagNode(tagNode* node) {
    free(node->name);
    freeAttrList(node->attr);
    free(node);
}