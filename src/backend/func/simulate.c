#include "../htpl.h"

void simulate() {

  nowTag = tagTree.root;
  
  int pc = 1;
  Operation* nowOperation;

  // for(int i=1; i<=totalLine; i++) printOperation(codes[i]);
  
  int exitFlag = 0;

  while(1) {
    // printf("loop... %d\n", pc);
    nowOperation = codes[pc];

    assert(0 < pc && pc <= totalLine);

    switch(nowOperation->opcode) {
      case OP_ORDER_ERROR: {
        pc++;
        exit(1);
        break;
      }
      case OP_ORDER_BUFFER: {
        if(nowOperation->operand1 > 0) {
          inputBuffer = newLinkedList();
          for(int i=0; i<nowOperation->operand1; i++) {
            pushBack(inputBuffer, newLinkedListNode(getchar()));
          }
        }
        else {
          inputBuffer = NULL;
        }

        pc++;
        break;
      }
      case OP_ORDER_TAG: {
        lists = (LinkedList**)malloc(sizeof(LinkedList*) * (nowOperation->operand1+1));
        for(int i=0; i<nowOperation->operand1+1; i++) {
          lists[i] = newLinkedList();
        }
        listsLength = nowOperation->operand1+1;

        pc++;
        break;
      }
      case OP_ORDER_OPEN: {
        LinkedListNode* parent = popBack(tagStack);
        parent->data++;
        nowTag = nthChild(nowTag, parent->data);
        pushBack(tagStack, parent);

        LinkedListNode* self = newLinkedListNode(-1);
        pushBack(tagStack, self);

        pc++;
        break;
      }
      case OP_ORDER_CLOSE: {
        nowTag = nowTag->parent;
        deleteBack(tagStack);

        pc++;
        break;
      }
      case OP_ORDER_POP: {
        LinkedListNode* temp = popMode == 1 ? popFront(lists[nowOperation->operand1]) : duplFront(lists[nowOperation->operand1]);
        pushBack(lists[nowOperation->operand2], temp);

        pc++;
        break;
      }
      case OP_ORDER_PUSH: {
        LinkedListNode* temp = newLinkedListNode(nowOperation->operand2);
        pushBack(lists[nowOperation->operand1], temp);

        pc++;
        break;
      }
      case OP_ORDER_DUPL: {
        LinkedListNode* temp = duplFront(lists[nowOperation->operand1]);
        pushBack(lists[nowOperation->operand2], temp);

        pc++;
        break;
      }
      case OP_ORDER_FLUSH: {
        // printf("FLUSH(%d) %d %d ", lists[nowOperation->operand1]->size, nowOperation->operand1, nowOperation->operand2);
        for(int i=0; i<nowOperation->operand2; i++) deleteFront(lists[nowOperation->operand1]);
        // printf("so size %d\n", lists[nowOperation->operand1]->size);

        pc++;
        break;
      }
      case OP_ORDER_ADD: {
        LinkedListNode* temp1 = popMode == 1 ? popFront(lists[nowOperation->operand1]) : duplFront(lists[nowOperation->operand1]);
        LinkedListNode* temp2 = popMode == 1 ? popFront(lists[nowOperation->operand1]) : duplSecond(lists[nowOperation->operand1]);
        LinkedListNode* result = newLinkedListNode(temp1->data + temp2->data + nowOperation->operand2);
        // printf("ADD %d %d %d = %d\n", temp1->data, temp2->data, nowOperation->operand2, result->data);
        pushBack(lists[nowOperation->operand1], result);

        pc++;
        break;
      }
      case OP_ORDER_JUMP: {
        // printf("now list size: %d\n", lists[(int)nowOperation->operand1]->size);
        // printf("jump success? ");
        LinkedListNode* temp = popMode == 1 ? popFront(lists[nowOperation->operand1]) : duplFront(lists[nowOperation->operand1]);
        if(temp->data != 0) {
          // printf("yes! go to ");
          nowTag = nowTag->parent;
          pc = nthChild(nowTag, getLast(tagStack)->data + nowOperation->operand2)->openingLine;

          deleteBack(tagStack);
          LinkedListNode* tagStackTop = popBack(tagStack);
          tagStackTop->data = nowTag->isNthChild;
          pushBack(tagStack, tagStackTop);

          // printf("%d\n", pc);
          // printf("now tagstack size: %d\n", tagStack->size);
        }
        else {
          // printf("no! go next\n");
          pc++;
        }

        break;
      }
      case OP_ORDER_BREAK: {
        LinkedListNode* temp = popMode == 1 ? popFront(lists[nowOperation->operand1]) : duplFront(lists[nowOperation->operand1]);
        if(temp->data == 0) {
          deleteBack(tagStack);
          nowTag = nowTag->parent;
          pc = nowTag->closingLine;
        }
        else {
          pc++;
        }

        break;
      }
      case OP_ORDER_PRINT: {
        LinkedListNode* temp = popMode == 1 ? popFront(lists[nowOperation->operand1]) : duplFront(lists[nowOperation->operand1]);
        // printf("PRINT: %d\n", temp->data);
        printf("%c", temp->data);

        pc++;
        break;
      }
      case OP_ORDER_SCAN: {
        LinkedListNode* temp = popFront(inputBuffer);
        pushBack(lists[nowOperation->operand1], temp);

        pc++;
        break;
      }
      case OP_ORDER_EXIT: {
        exitFlag = 1;
        break;
      }
      case OP_ORDER_POPMODE: {
        popMode = !(nowOperation->operand1 == 0);
        // printf("now popmode %d\n", popMode);

        pc++;
        break;
      }
    }

    if(exitFlag) break;
  }
}