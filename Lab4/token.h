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

char *keywords[] = {
    "int","float","char","double","void",
    "if","else","while","for","return"
};
int keywordCount = 10;

int isKeyword(char *);
int isArithmetic(char *);
int isRelational(char *);
int isLogical(char *);
int isSpecialSymbol(char);
int isIdentifier(char *);
int isNumber(char *);
int isStringLiteral(char *);

int isKeyword(char *lex) {
    for (int i = 0; i < keywordCount; i++)
        if (strcmp(lex, keywords[i]) == 0)
            return 1;
    return 0;
}

int isArithmetic(char *lex) {
    return (!strcmp(lex,"+") || !strcmp(lex,"-") ||
            !strcmp(lex,"*") || !strcmp(lex,"/") ||
            !strcmp(lex,"%"));
}

int isRelational(char *lex) {
    return (!strcmp(lex,"<") || !strcmp(lex,">") ||
            !strcmp(lex,"<=") || !strcmp(lex,">=") ||
            !strcmp(lex,"==") || !strcmp(lex,"!="));
}

int isLogical(char *lex) {
    return (!strcmp(lex,"&&") || !strcmp(lex,"||") ||
            !strcmp(lex,"!"));
}

int isSpecialSymbol(char ch) {
    return (ch=='('||ch==')'||ch=='{'||ch=='}'||
            ch==';'||ch==',' );
}

int isIdentifier(char *lex) {
    if (!isalpha(lex[0]) && lex[0] != '_')
        return 0;
    for (int i = 1; lex[i]; i++)
        if (!isalnum(lex[i]) && lex[i] != '_')
            return 0;
    return 1;
}

int isNumber(char *lex) {
    for (int i = 0; lex[i]; i++)
        if (!isdigit(lex[i]))
            return 0;
    return 1;
}

int isStringLiteral(char *lex) {
    int len = strlen(lex);
    return (lex[0]=='"' && lex[len-1]=='"');
}

#endif
