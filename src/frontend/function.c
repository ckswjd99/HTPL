#include "htpl.h"

/* ATTRIBUTE HANDLER */
void freeAttrList(attrNode* list) {
    if(list == NULL) return;

    attrNode *temp1, *temp2 = list;

    while(temp2 != NULL) {
        temp1 = temp2;
        temp2 = temp1->next;

        free(temp1);
    }
}

int getAttrListLen(attrNode* list) {
    int length = 0;
    while(list != NULL) {
        length++;
        list = list->next;
    }

    return length;
}

void printAttrList(attrNode* list) {
    attrNode* temp = list;
    printf("attribute list: ");
    while(temp != NULL) {
        printf("%s=\"%s\" ", temp->data->name, temp->data->value);
        temp = temp->next;
    }
    printf("\n");
}


/* TAG OPEN STACK */
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

void freeTagNode(tagNode* node) {
    free(node->name);
    freeAttrList(node->attr);
    free(node);
}