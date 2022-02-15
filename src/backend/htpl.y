%{

#include "htpl.h"

int yylex();
int yyerror(char* s);

%}

%union {
  int opcode;
  char number;
  char* charPtr;
  Operation* instPtr;
}

%token<opcode> OP_ERROR OP_BUFFER OP_TAG OP_OPEN OP_CLOSE OP_POP OP_PUSH OP_DUPL OP_STASH OP_ADD OP_JUMP OP_BREAK OP_PRINT OP_SCAN OP_EXIT
%token<number> OPERAND NEW_LINE
%type<instPtr> instruction

%%
assembly
  : line_list
  ;

line_list 
  : line line_list 
    {

    }
  | /* empty */
  ;

line
  : instruction NEW_LINE {
    int nthLine = readLine() - 1;
    codes[nthLine] = $1;
    // printf("line parsed: %d\n", nthLine);
  }

instruction
  : OP_ERROR
    {
      printErrorMsg("invalid operation code");
      exit(1);
    }
  | OP_BUFFER OPERAND
    {
      $$ = newOperation($1, $2, 0);
    }
  | OP_TAG OPERAND
    {
      $$ = newOperation($1, $2, 0);
    }
  | OP_OPEN OPERAND
    {
      TagTreeNode* temp = newTag($1);
      appendChild(nowTag, temp);
      nowTag = temp;
      $$ = newOperation($1, $2, 0);
    }
  | OP_CLOSE OPERAND
    {
      closeTag(nowTag);
      nowTag = nowTag->parent;
      $$ = newOperation($1, $2, 0);
    }
  | OP_POP OPERAND OPERAND
    {
      $$ = newOperation($1, $2, $3, 0);
    }
  | OP_PUSH OPERAND OPERAND
    {
      $$ = newOperation($1, $2, $3, 0);
    }
  | OP_DUPL OPERAND OPERAND
    {
      $$ = newOperation($1, $2, $3, 0);
    }
  | OP_STASH OPERAND OPERAND
    {
      $$ = newOperation($1, $2, $3, 0);
    }
  | OP_ADD OPERAND OPERAND
    {
      $$ = newOperation($1, $2, $3, 0);
    }
  | OP_JUMP OPERAND OPERAND
    {
      $$ = newOperation($1, $2, $3, 0);
    }
  | OP_BREAK
    {
      $$ = newOperation($1, 0);
    }
  | OP_PRINT OPERAND
    {
      $$ = newOperation($1, $2, 0);
    }
  | OP_SCAN OPERAND
    {
      $$ = newOperation($1, $2, 0);
    }
  | OP_EXIT
    {
      $$ = newOperation($1, 0);
    }
%%

int yyerror(char* s)
{
	fprintf(stderr,"%d:%s\n",readLine(),s);
	exit (-1);
}

void printErrorMsg(char* format, ...) {
  char buf[512] = {0,};
  va_list ap;

  sprintf(buf, "%s:%d: error:", filename, readLine());
  vsprintf(buf+strlen(buf), format, ap);
  strcpy(buf+strlen(buf), "\n");
  va_end(ap);

  printf("%s", buf);
}
