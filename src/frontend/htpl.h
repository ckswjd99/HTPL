#ifndef __HTPL_H__
#define __HTPL_H__

#include <string.h>
#include <stdio.h>

// VALUE TYPE
#define _NUMBER 0
#define _TEXT 1

// OPERATION TYPE
#define PLUS 0
#define MINUS 1
#define MULT 2
#define DIV 3
#define NOT 4
#define SAME_WITH 5
#define LESS_THAN 6
#define BIGGER_THAN 7


typedef struct decl {
    char* name;
    char type;
    char number;
    char* text;
} decl;

#endif