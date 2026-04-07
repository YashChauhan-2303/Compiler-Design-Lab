#include "token.h"
#include <stdlib.h>
#include <stdio.h>

extern FILE *fp;

struct token lookahead;

int getNextToken(struct token *);

void error_expected(const char *exp) {
    printf("Error at row %u, column %u: expected %s, found %s\n",
           lookahead.row, lookahead.col, exp, lookahead.token_name);
    exit(1);
}

void match(const char *t) {
    if (strcmp(t, "id") == 0 || strcmp(t, "num") == 0) {
        if (strcmp(lookahead.type, t) == 0) {
            if (!getNextToken(&lookahead))
                strcpy(lookahead.token_name, "EOF");
        } else {
            error_expected(t);
        }
    } else {
        if (strcmp(lookahead.token_name, t) == 0) {
            if (!getNextToken(&lookahead))
                strcpy(lookahead.token_name, "EOF");
        } else {
            error_expected(t);
        }
    }
}

void identifier_list();
void declarations();
void assign_stat();
void program();

void identifier_list() {
    match("id");
    if (strcmp(lookahead.token_name, ",") == 0) {
        match(",");
        identifier_list();
    }
}

void declarations() {
    if (strcmp(lookahead.token_name, "int") == 0 ||
        strcmp(lookahead.token_name, "char") == 0) {

        match(lookahead.token_name);
        identifier_list();
        match(";");
        declarations();
    }
}

void assign_stat() {
    match("id");
    match("=");
    if (strcmp(lookahead.type, "id") == 0)
        match("id");
    else if (strcmp(lookahead.type, "num") == 0)
        match("num");
    else
        error_expected("id or num");
    match(";");
}

void program() {
    match("main");
    match("(");
    match(")");
    match("{");
    declarations();
    assign_stat();
    match("}");
}

int main() {
    fp = stdin;

    if (!getNextToken(&lookahead)) {
        printf("Empty input\n");
        return 0;
    }
    
    program();
    printf("Parsing successful\n");
    return 0;
}