#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct token {
    char token_name[50];
    int index;
    unsigned int row, col;
    char type[30];
};

extern char *keywords[];
extern int keywordCount;

int isKeyword(char *);
int isArithmetic(char *);
int isRelational(char *);
int isLogical(char *);
int isSpecialSymbol(char);

#endif