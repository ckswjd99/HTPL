%{
#include "htpl.h"
#include "htpl.tab.h"

static int lineno = 1;
int lexDebug = 0;
%}

white_space		[ \t]+
tag_name_char   [0-9a-zA-Z\-\_]
attr_value_char [^\<\>\/ \n\t=\"]
special_char	\\[nt]

%start INTAG OUTTAG
%start COMMENT

%%

 /* COMMENT */
<OUTTAG>"<!--" { if(lexDebug) printf("%s\n", yytext); BEGIN COMMENT; }
<COMMENT>"-->" { if(lexDebug) printf("%s\n", yytext); BEGIN OUTTAG; }

 /* TAG PARSER */
<OUTTAG>"<" { 
    if(lexDebug) printf("CT OPEN %s\n", yytext);
    BEGIN INTAG;
    return COMMONTAG_OPEN_START;
}

<OUTTAG>"<"/[^\<\>]*"/"{white_space}?">" { 
    if(lexDebug) printf("ST %s\n", yytext);
    BEGIN INTAG;
    return SINGLETAG_START;
}

<OUTTAG>"<"{white_space}?"/" { 
    if(lexDebug) printf("CT CLOSE %s\n", yytext);
    BEGIN INTAG;
    return COMMONTAG_CLOSE_START;
}

<OUTTAG>"<"{white_space}?"!"{white_space}?"DOCTYPE"{white_space}?[^\<\>\/]*">" { 
    if(lexDebug) printf("%s\n", yytext);
    return DOCTYPE_TAG;
}

<INTAG>"/>" { 
    if(lexDebug) printf("ST %s\n", yytext);
    BEGIN OUTTAG;
    return SINGLETAG_END;
}

<INTAG>">" { 
    if(lexDebug) printf("TAG END %s\n", yytext);
    BEGIN OUTTAG;
    return TAG_END;
}


 /* INTAG PARSER */
<INTAG>{tag_name_char}+/{white_space}|">"|"/>" {   // TAG NAME
    if(lexDebug) printf("TAG NAME: %s\n", yytext);
    yylval.stringVal = strdup(yytext);
    
    if(strcmp(yytext, "html") == 0) {
        return HTML;
    }
    else if(strcmp(yytext, "head") == 0) {
        return HEAD;
    }
    else if(strcmp(yytext, "body") == 0) {
        return BODY;
    }
    else {
        return TAG_NAME;
    }
}
<INTAG>{tag_name_char}+/= { // ATTR NAME
    if(lexDebug) printf("ATTR NAME: %s\n", yytext);
    yylval.stringVal = strdup(yytext);
    return ATTR_NAME;
}
<INTAG>"=" {    // "="
    if(lexDebug) printf("%s\n", yytext);
    return '=';
}
<INTAG>\"{attr_value_char}+\" {   // ATTR VALUE
    yytext[yyleng-1] = '\0';
    yylval.stringVal = strdup(yytext+1);
    if(lexDebug) printf("ATTR VAL: %s\n", yytext+1);
    return ATTR_VAL;
}

 /* INNER EXPRESSIONS */
<OUTTAG>"SAME WITH" { 
    if(lexDebug) printf("OPERATOR: %s\n", yytext);
    return SAME;
}
<OUTTAG>"LESS THAN" { 
    if(lexDebug) printf("OPERATOR: %s\n", yytext);
    return LESS;
}
<OUTTAG>"BIGGER THAN" { 
    if(lexDebug) printf("OPERATOR: %s\n", yytext);
    return BIGGER;
}
<OUTTAG>"PLUS" { 
    if(lexDebug) printf("OPERATOR: %s\n", yytext);
    return PLUS;
}
<OUTTAG>"MINUS" { 
    if(lexDebug) printf("OPERATOR: %s\n", yytext);
    return MINUS;
}
<OUTTAG>"MULT" { 
    if(lexDebug) printf("OPERATOR: %s\n", yytext);
    return MULT;
}
<OUTTAG>"DIV" { 
    if(lexDebug) printf("OPERATOR: %s\n", yytext);
    return DIVIDE;
}
<OUTTAG>[0-9]+ { 
    if(lexDebug) printf("NUMBER: %s\n", yytext);
    yylval.intVal = atoi(yytext);
    return NUMBER_CONST;
}
<OUTTAG>\"({special_char}|[^\\\"\n\<\>])*\" { 
    if(lexDebug) printf("STRING: %s\n", yytext);
    yylval.stringVal = yytext;
    return STRING;
}




"\n" { lineno++; }

{white_space} { ; }
. { ; }


%%

int main(int argc, char* argv[]) {
    filename = argv[1];
    yyin = fopen(filename, "r");

    errorMute = 0;

    BEGIN OUTTAG;

    initTagStack();

    yyparse();
}

int getLineNum() {
    return lineno;
}