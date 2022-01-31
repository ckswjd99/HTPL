%{
#include "htpl.h"


static int lineno = 1;

static int tagOpen = 0;
%}

white_space		[ \t]+

%start INTAG OUTTAG
%start COMMENT

%%

<OUTTAG>"<" { 
    printf("<commontag"); 
    BEGIN INTAG;
}

<OUTTAG>"<"/[^\>]*"/>" { 
    printf("<singletag"); 
    BEGIN INTAG;
}

<OUTTAG>"</" { 
    printf("</commontag"); 
    BEGIN INTAG;
}

<OUTTAG>"<!" { 
    printf("<!specialtag"); 
    BEGIN INTAG;
}

<INTAG>">" { 
    printf(">\n"); 
    BEGIN OUTTAG;
}

<INTAG>"/>" { 
    printf("/>\n"); 
    BEGIN OUTTAG;
}

<OUTTAG>"<!--" {
    BEGIN COMMENT;
}
<COMMENT>"-->" {
    BEGIN OUTTAG;
}

{white_space} { ; }

. { ; }


%%

int main(int argc, char* argv[]) {
    yyin = fopen(argv[1], "r");

    BEGIN OUTTAG;

    yylex();
}