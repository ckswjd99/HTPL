#include "../htpl.h"

const char* rawOperations[] = {
  "NULL", "BUFFER", "TAG", "OPEN", "CLOSE", "POP", "PUSH", "DUPL", "STASH", "ADD", "JUMP", "BREAK", "PRINT", "SCAN", "EXIT", NULL
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

Operation* newOperation(int opcode, ...) {
  Operation* temp = (Operation*)malloc(sizeof(Operation));
  temp->opcode = opcode;
  
  va_list ap;
  va_start(ap, opcode);
  
  char tempChar = va_arg(ap, int);
  if(tempChar == 0) return temp;
  else temp->operand1 = tempChar;

  tempChar = va_arg(ap, int);
  if(tempChar == 0) return temp;
  else temp->operand2 = tempChar;

  return temp;
}

void printOperation(Operation* operation) {
  printf("OP %d OPERAND %d %d\n", operation->opcode, operation->operand1, operation->operand2);
}