#include "htpl.h"

#define HASH_TABLE_SIZE 101

typedef struct hashNode {
    struct hashNode* next;
    decl* decl;
} hashNode;

static hashNode* hashTable[HASH_TABLE_SIZE];

decl* enter(int type, char* name, int length) {
    int hashIndex = 0;
    for(int i=0; i<length; i++) hashIndex += (int)name[i];
    hashIndex = hashIndex % HASH_TABLE_SIZE;

    if(hashTable[hashIndex] == NULL) {
        hashTable[hashIndex] = (hashNode*)malloc(sizeof(hashNode));
        hashTable[hashIndex]->next = NULL;
        hashTable[hashIndex]->decl = (decl*)malloc(sizeof(decl));
        hashTable[hashIndex]->decl->name = name;
        hashTable[hashIndex]->decl->value = (value*)malloc(sizeof(value));
        hashTable[hashIndex]->decl->value->type = type;

        return hashTable[hashIndex]->decl;
    }
    else {
        hashNode* enterList = hashTable[hashIndex];
        int exist = 0;
        while(1) {
            if(strcmp(enterList->decl->name, name) == 0) {
                exist = 1;
                break;
            }
            if(enterList->next == NULL) break;
            enterList = enterList->next;
        }

        if(exist) {
            return enterList->decl;
        }
        else {
            enterList->next = (hashNode*)malloc(sizeof(hashNode));
            enterList->next->next = NULL;
            enterList->next->decl = (decl*)malloc(sizeof(decl));
            enterList->next->decl->name = name;
            enterList->next->decl->value = (value*)malloc(sizeof(value));
            enterList->next->decl->value->type = type;


            return enterList->next->decl;
        }
    }
}

int isDeclared(char* name, int length) {
    int hashIndex = 0;
    for(int i=0; i<length; i++) hashIndex += (int)name[i];
    hashIndex = hashIndex % HASH_TABLE_SIZE;

    if(hashTable[hashIndex] == NULL) {
        return 0;
    }
    else {
        hashNode* enterList = hashTable[hashIndex];
        int exist = 0;
        while(1) {
            if(strcmp(enterList->decl->name, name) == 0) {
                exist = 1;
                break;
            }
            if(enterList->next == NULL) break;
            enterList = enterList->next;
        }

        return exist;
    }
}

/** DEBUG **/
// #include <stdio.h>
// int main() {
//     printf("check hi: %d\n", isDeclared("hi", 2));
//     printf("declare hi: %p\n", enter(_NUMBER, "hi", 2));
//     printf("check hi: %d\n", isDeclared("hi", 2));

//     return 0;
// }