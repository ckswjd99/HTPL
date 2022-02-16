%{

#include "htpl.h"
#include "htpl.tab.h"

int lineno = 1;

int bufferInit = 0;
int tagInit = 0;

%}

Operation [a-zA-Z|_]+
Digit [0-9]
WhiteSpace [ \t]+

%%

{Operation} {
  int opcode = parseOpcode(yytext);
  yylval.opcode = opcode;

  if(opcode == OP_ORDER_ERROR) {
    fprintf(stderr, "line %d: error:invalid operation %s\n", lineno, yytext);
    return OP_ERROR;
  }
  else if(opcode == OP_ORDER_BUFFER) {
    assert(!bufferInit);
    bufferInit = 1;
    return OP_BUFFER;
  }
  else if(opcode == OP_ORDER_TAG) {
    assert(!tagInit);
    tagInit = 1;
    return OP_TAG;
  }
  
  assert(bufferInit && tagInit);

  switch(opcode) {
    case OP_ORDER_OPEN: return OP_OPEN;
    case OP_ORDER_CLOSE: return OP_CLOSE;
    case OP_ORDER_POP: return OP_POP;
    case OP_ORDER_PUSH: return OP_PUSH;
    case OP_ORDER_DUPL: return OP_DUPL;
    case OP_ORDER_FLUSH: return OP_FLUSH;
    case OP_ORDER_ADD: return OP_ADD;
    case OP_ORDER_JUMP: return OP_JUMP;
    case OP_ORDER_BREAK: return OP_BREAK;
    case OP_ORDER_PRINT: return OP_PRINT;
    case OP_ORDER_SCAN: return OP_SCAN;
    case OP_ORDER_EXIT: return OP_EXIT;
    case OP_ORDER_POPMODE: return OP_POPMODE;
  }
}

{Digit}+ {
  yylval.number = atoi(yytext);
  return OPERAND;
}

{WhiteSpace} {

}

[\n] {
  lineno++;
  return NEW_LINE;
}

.	{
	fprintf(stderr,"line %d: error\n",lineno);
}
%%

int readLine() {
  return lineno;
}

void init() {
  popMode = 1;

  tagTree.root = (TagTreeNode*)malloc(sizeof(TagTreeNode));
  tagTree.root->parent = NULL;
  tagTree.root->nextSibling = NULL;
  tagTree.root->children = NULL;

  nowTag = tagTree.root;

  tagStack = newLinkedList();
  pushBack(tagStack, newLinkedListNode(-1));
}

int main(int argc, char* argv[]) {
  yyin = fopen(argv[1], "r");
  filename = argv[1];

  if(!yyin) {
		printf("Can't open input stream!\n");
		exit(1);
	}

  
  FILE* tempFile = fopen(argv[1], "r");
  for (char c = getc(tempFile); c != EOF; c = getc(tempFile))
    if (c == '\n') totalLine = totalLine + 1;
  fclose(tempFile);
  codes = (Operation**)malloc(sizeof(Operation*) * (totalLine+1));

  init();

	yyparse();
  
  // printTag(tagTree.root);
  // printf("parsed!\n");
  simulate();

	fclose(yyin);
	return 0;
}