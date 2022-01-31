%{
    
%}

%union {
    char*    stringVal;
}

%token TAG_OPEN, END_TAG_OPEN, START_TAG_CLOSE, END_TAG_CLOSE, SINGLE_TAG_CLOSE
%token DOCTYPE
%token<stringVal> TAG_NAME, ATTRIBUTE_NAME, ATTRIBUTE_VAL

%%
program : DOCTYPE head body;

head : clause_list;

body : clause_list;

clause_list
    : clause clause_list {}
    | /* empty */ {}

clause
    : tag_start clause_list tag_end {}
    | single_tag {}

tag_start : TAG_OPEN TAG_NAME attribute_list START_TAG_CLOSE

tag_end : END_TAG_OPEN TAG_NAME END_TAG_CLOSE

single_tag : TAG_OPEN TAG_NAME attribute_list SINGLE_TAG_CLOSE

attribute_list 
    : attribute attribute_list {}
    | /* empty */ {}

attribute : ATTRIBUTE_NAME '=' ATTRIBUTE_VAL

%%