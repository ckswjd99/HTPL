#ifndef __QUEUE_MACHINE
#define __QUEUE_MACHINE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

/* OPERATION */

#define OP_ORDER_ERROR 0
#define OP_ORDER_BUFFER 1
#define OP_ORDER_TAG 2
#define OP_ORDER_OPEN 3
#define OP_ORDER_CLOSE 4
#define OP_ORDER_POP 5
#define OP_ORDER_PUSH 6
#define OP_ORDER_DUPL 7
#define OP_ORDER_STASH 8
#define OP_ORDER_ADD 9
#define OP_ORDER_JUMP 10
#define OP_ORDER_BREAK 11
#define OP_ORDER_PRINT 12
#define OP_ORDER_SCAN 13
#define OP_ORDER_EXIT 14

typedef struct Operation
{
  char opcode;
  char operand1;
  char operand2;
} Operation;

int parseOpcode(char* operation);
Operation* newOperation(int opcode, ...);
void printOperation(Operation* operation);
Operation **codes;

/* LINKED LIST */
typedef struct LinkedListNode
{
  struct LinkedListNode *next;
  char data;

} LinkedListNode;

typedef struct LinkedList
{
  char size;
  LinkedListNode *head;

} LinkedList;

LinkedListNode *newLinkedListNode(char data);
LinkedList *newLinkedList();
LinkedListNode *popFront(LinkedList *linkedList);
LinkedListNode *popBack(LinkedList *linkedList);
LinkedListNode *duplFront(LinkedList *linkedList);
LinkedListNode *getLast(LinkedList *linkedList);
void pushBack(LinkedList *linkedList, LinkedListNode *value);
void deleteFront(LinkedList *linkedList);
void printLinkedList(LinkedList* linkedList);

/* TAG TREE */
typedef struct TagTreeNode
{
  struct TagTreeNode *parent;
  struct TagTreeNode *nextSibling;
  struct TagTreeNode *children;

  char linkedListIndex;
  char isNthChild;
  char childrenLength;

  int openingLine;
  int closingLine;

} TagTreeNode;

typedef struct TagTree
{
  TagTreeNode *root;

} TagTree;

TagTreeNode *newTag(char index);
void closeTag(TagTreeNode* tag);
TagTreeNode *nthChild(TagTreeNode *tagTreeNode, char value);
TagTreeNode *jumpSibling(TagTreeNode *tagTreeNode, char value);
void *appendChild(TagTreeNode* parent, TagTreeNode* child);
void printTag(TagTreeNode* tag);


/* BASICS */
void printErrorMsg(char* format, ...);

char* filename;
int readLine();
int totalLine;

LinkedList* inputBuffer;
LinkedList** lists;
int listsLength;
TagTree tagTree;
TagTreeNode* nowTag;
LinkedList* tagStack;

void init();
void simulate();

#endif