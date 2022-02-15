#include "../htpl.h"

const char* rawOperations[] = {
  "NULL", "BUFFER", "TAG", "OPEN", "CLOSE", "POP", "PUSH", "DUPL", "FLUSH", "ADD", "JUMP", "BREAK", "PRINT", "SCAN", "EXIT", "POPMODE", NULL
};

int parseOpcode(char* operation) {
  int i = 1;
  while(rawOperations[i] != NULL) {
    if(strcmp(rawOperations[i], operation) == 0) {
      return i;
    }
    i++;
  }
  return OP_ORDER_ERROR;
}

Operation* newOperation(int opcode, char operand1, char operand2) {
  Operation* temp = (Operation*)malloc(sizeof(Operation));
  temp->opcode = opcode;
  temp->operand1 = operand1;
  temp->operand2 = operand2;

  return temp;
}

void printOperation(Operation* operation) {
  printf("OP %d OPERAND %d %d\n", operation->opcode, operation->operand1, operation->operand2);
}