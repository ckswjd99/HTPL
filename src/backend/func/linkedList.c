#include "../htpl.h"

LinkedListNode *newLinkedListNode(char data) {
  LinkedListNode* temp = (LinkedListNode*)malloc(sizeof(LinkedListNode));
  temp->data = data;
  temp->next = NULL;
  return temp;
}

LinkedList* newLinkedList() {
  LinkedList* temp = (LinkedList*)malloc(sizeof(LinkedList));
  temp->size = 0;
  temp->head = (LinkedListNode*)malloc(sizeof(LinkedListNode));
  temp->head->next = NULL;

  return temp;
}

LinkedListNode *popFront(LinkedList *linkedList) {
  if(linkedList->size == 0) {
    LinkedListNode* temp = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    temp->data = 0;
    temp->next = NULL;
    return temp;
  }

  LinkedListNode* temp = linkedList->head->next;
  linkedList->head->next = temp->next;
  linkedList->size--;
  temp->next = NULL;
  return temp;
}

LinkedListNode *popBack(LinkedList *linkedList) {
  if(linkedList->size == 0) return NULL;
  else if(linkedList->size == 1) {
    LinkedListNode* temp = linkedList->head->next;
    linkedList->head->next = NULL;
    linkedList->size = 0;
    return temp;
  }

  LinkedListNode* temp = linkedList->head;
  while(temp->next->next != NULL) temp = temp->next;
  LinkedListNode* result = temp->next;
  temp->next = NULL;
  linkedList->size--;

  return result;
}

LinkedListNode *duplFront(LinkedList *linkedList) {
  LinkedListNode* temp = (LinkedListNode*)malloc(sizeof(LinkedListNode));
  if(linkedList->size == 0) {
    temp->data = 0;
    temp->next = NULL;  
  }
  else {
    temp->data = linkedList->head->next->data;
    temp->next = NULL;
  }
  return temp;
}

LinkedListNode *duplSecond(LinkedList *linkedList) {
  LinkedListNode* temp = (LinkedListNode*)malloc(sizeof(LinkedListNode));
  if(linkedList->size < 2) {
    temp->data = 0;
    temp->next = NULL;  
  }
  else {
    temp->data = linkedList->head->next->next->data;
    temp->next = NULL;
  }
  return temp;
}

LinkedListNode *getLast(LinkedList *linkedList) {
  LinkedListNode* temp = linkedList->head;
  while(temp->next != NULL) temp = temp->next;
  return temp;
}

void pushBack(LinkedList *linkedList, LinkedListNode *node) {
  LinkedListNode* temp = linkedList->head;
  while(temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = node;
  linkedList->size++;
}

void deleteFront(LinkedList *linkedList) {
  if(linkedList->size == 0) return;

  LinkedListNode* temp = linkedList->head->next;
  linkedList->head->next = temp->next;
  linkedList->size--;
  free(temp);
}

void deleteBack(LinkedList *linkedList) {
  if(linkedList->size == 0) return;
  else if(linkedList->size == 1) {
    LinkedListNode* temp = linkedList->head->next;
    linkedList->head->next = NULL;
    linkedList->size = 0;

    free(temp);
    return;
  }

  LinkedListNode* temp = linkedList->head;
  while(temp->next->next != NULL) temp = temp->next;
  LinkedListNode* result = temp->next;
  temp->next = NULL;
  linkedList->size--;

  free(result);
  return;
}

void printLinkedList(LinkedList* linkedList) {
  printf("%p\n", linkedList->head->next);
  LinkedListNode* temp = linkedList->head->next;
  printf("Linked List(%d): ", linkedList->size);
  while(temp != NULL) {
    printf("%d", temp->data);
    temp = temp->next;
  }
  printf("\n");
}