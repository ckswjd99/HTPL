#include "../htpl.h"

TagTreeNode *newTag(char index) {
  TagTreeNode* temp = (TagTreeNode*)malloc(sizeof(TagTreeNode));

  temp->parent = NULL;
  temp->nextSibling = NULL;
  temp->children = NULL;

  temp->linkedListIndex = index;
  temp->isNthChild = 0;
  temp->childrenLength = 0;

  temp->openingLine = readLine();
  temp->closingLine = 0;

  return temp;
}

void closeTag(TagTreeNode* tag) {
  tag->closingLine = readLine();
}

TagTreeNode *nthChild(TagTreeNode *tagTreeNode, char value) {
  TagTreeNode* temp = tagTreeNode->children;
  for(char i=0; i<value; i++) temp = temp->nextSibling;
  return temp;
}

TagTreeNode *jumpSibling(TagTreeNode *tagTreeNode, char value) {
  TagTreeNode* temp = tagTreeNode;
  for(char i=0; i<value; i++) temp = temp->nextSibling;
  return temp;
}

void *appendChild(TagTreeNode* parent, TagTreeNode* child) {
  if(parent->childrenLength == 0) {
    parent->children = child;
    
    child->parent = parent;
    child->nextSibling = child;
    child->isNthChild = 0;
  }
  else {
    TagTreeNode* lastChild = nthChild(parent, parent->childrenLength-1);
    child->parent = parent;
    lastChild->nextSibling = child;
    child->nextSibling = parent->children;

    child->isNthChild = parent->childrenLength;
  }

  parent->childrenLength++;
}

void printTag(TagTreeNode* tag) {
  printf("OPEN TAG AT %d\n", tag->openingLine);
  for(int i=0; i<tag->childrenLength; i++) {
    printTag(nthChild(tag, i));
  }
  printf("CLOSE TAG AT %d\n", tag->closingLine);
}