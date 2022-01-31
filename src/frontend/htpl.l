%{
#include "htpl.h"

static int lineno = 1;
%}

white_space		[ \t]+
tag_char    [\/\<\>]

%start INTAG OUTTAG SPECIALTAG
%start COMMENT

%%

 /* TAG PARSER */
<OUTTAG>"<" { 
    BEGIN INTAG;
    // return COMMONTAG_OPEN_START;
}

<OUTTAG>"<"/[^\>]*"/>" { 
    BEGIN INTAG;
    // return SINGLETAG_START;
}

<OUTTAG>"</" { 
    BEGIN INTAG;
    // return COMMONTAG_CLOSE_START;
}

<OUTTAG>"<!"{white_space}?"DOCTYPE"{white_space}?[^\<\>\/]*">" { 
    printf("doctype! %s\n", yytext);
    // return DOCTYPE_TAG;
}

<INTAG>"/>" { 
    BEGIN OUTTAG;
    // return SINGLETAG_END;
}

<INTAG>">" { 
    BEGIN OUTTAG;
    // return TAG_END;
}

 /* INTAG PARSER */
<INTAG>([^\<\>\/ \n\t=\"])+ {   // TAG NAME
    printf("tagname: %s\n", yytext);
}
<INTAG>([^\<\>\/ \n\t=\"])+/= { // ATTR NAME
    printf("%s", yytext);
}
<INTAG>"=" {    // "="
    printf(" = ");
}
<INTAG>\"([^\<\>\/ \n\t=\"])+\" {   // ATTR VALUE
    printf("%s\n", yytext);
}



 /* OTHERS */
<OUTTAG>"<!--" { BEGIN COMMENT; }
<COMMENT>"-->" { BEGIN OUTTAG; }

"\n" { lineno++; }

{white_space} { ; }
. { ; }


%%

int main(int argc, char* argv[]) {
    yyin = fopen(argv[1], "r");

    BEGIN OUTTAG;

    yylex();
}