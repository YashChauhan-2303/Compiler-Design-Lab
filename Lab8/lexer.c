#include "token.h"
#include <stdlib.h>

FILE *fp;
unsigned int row = 1, col = 0;

char *keywords[] = {
    "int","float","char","double","void",
    "if","else","while","for","return"
};
int keywordCount = 10;

int checkKeyword(char *lex, int i) {
    if (i == keywordCount) return 0;
    if (strcmp(lex, keywords[i]) == 0) return 1;
    return checkKeyword(lex, i + 1);
}

int isKeyword(char *lex) {
    return checkKeyword(lex, 0);
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
            ch==';'||ch==','||ch=='['||ch==']');
}

void buildIdentifier(char *buf, int *i) {
    char c = fgetc(fp);
    if (isalnum(c) || c == '_') {
        buf[(*i)++] = c;
        col++;
        buildIdentifier(buf, i);
    } else {
        ungetc(c, fp);
    }
}

void buildNumber(char *buf, int *i) {
    char c = fgetc(fp);
    if (isdigit(c)) {
        buf[(*i)++] = c;
        col++;
        buildNumber(buf, i);
    } else {
        ungetc(c, fp);
    }
}

int getNextToken(struct token *t) {
    char c = fgetc(fp);
    if (c == EOF) return 0;

    col++;

    if (c == '\n') {
        row++; col = 0;
        return getNextToken(t);
    }

    if (isspace(c))
        return getNextToken(t);

    int i = 0;

    if (isalpha(c) || c == '_') {
        t->row = row; t->col = col;
        t->token_name[i++] = c;
        buildIdentifier(t->token_name, &i);
        t->token_name[i] = '\0';

        if (isKeyword(t->token_name))
            strcpy(t->type, "KEYWORD");
        else
            strcpy(t->type, "id");

        return 1;
    }

    if (isdigit(c)) {
        t->row = row; t->col = col;
        t->token_name[i++] = c;
        buildNumber(t->token_name, &i);
        t->token_name[i] = '\0';
        strcpy(t->type, "num");
        return 1;
    }

    t->row = row; t->col = col;
    t->token_name[i++] = c;

    char next = fgetc(fp);
    if (next == '=' || (c=='&' && next=='&') || (c=='|' && next=='|')) {
        t->token_name[i++] = next;
    } else {
        ungetc(next, fp);
    }

    t->token_name[i] = '\0';

    if (isArithmetic(t->token_name))
        strcpy(t->type, "ARITHMETIC OPERATOR");
    else if (isRelational(t->token_name))
        strcpy(t->type, "RELATIONAL OPERATOR");
    else if (!strcmp(t->token_name, "="))
        strcpy(t->type, "ASSIGNMENT OPERATOR");
    else if (isLogical(t->token_name))
        strcpy(t->type, "LOGICAL OPERATOR");
    else if (isSpecialSymbol(c))
        strcpy(t->type, "SPECIAL SYMBOL");
    else
        strcpy(t->type, "UNKNOWN");

    return 1;
}