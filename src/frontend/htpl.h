#ifndef __HTPL_H__
#define __HTPL_H__

#include <string.h>
#include <stdio.h>

// VALUE TYPE
#define _NUMBER 0
#define _TEXT 1


typedef struct decl {
    char* name;
    char type;
    char number;
    char* text;
} decl;

#endif