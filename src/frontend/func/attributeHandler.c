#include "../htpl.h"

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

attrNode* findAttrByName(attrNode* list, char* name) {
    attrNode* temp = list;
    while(1) {
        if(strcmp(temp->data->name, name) == 0 || temp == NULL) {
            break;
        }
        temp = temp->next;
    }

    return temp;
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