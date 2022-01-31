%{
    
%}

%union {
    char*    stringVal;
}

%token COMMONTAG_OPEN_START, COMMONTAG_CLOSE_START, SINGLETAG_START, SINGLETAG_END, TAG_END
%token DOCTYPE_TAG, HEAD, BODY
%token<stringVal> TAG_NAME, ATTRIBUTE_NAME, ATTRIBUTE_VAL

%%
program: DOCTYPE_TAG structure

structure: html_open head body html_close

html_open: COMMONTAG_OPEN_START TAG_NAME TAG_END



%%