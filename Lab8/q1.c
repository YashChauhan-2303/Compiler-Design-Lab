#include "token.h"
#include <stdlib.h>
#include <stdio.h>

extern FILE *fp;

struct token lookahead;
int error_count = 0;

int getNextToken(struct token *);

void printToken(struct token t) {
    printf("<%s,%s,%u,%u>\n", t.token_name, t.type, t.row, t.col);
}

void skipTokens() {
    if (!strcmp(lookahead.token_name, ";") ||
        !strcmp(lookahead.token_name, "}"))
        return;

    if (!getNextToken(&lookahead))
        return;

    skipTokens();
}

void error_expected(const char *exp) {
    printf("Error at row %u, col %u: expected %s, found %s\n",
           lookahead.row, lookahead.col, exp, lookahead.token_name);

    error_count++;
    skipTokens();

    if (!strcmp(lookahead.token_name, ";"))
        getNextToken(&lookahead);
}

void match(const char *t) {
    if (!strcmp(t,"id") || !strcmp(t,"num")) {
        if (!strcmp(lookahead.type,t)) {
            printToken(lookahead);
            getNextToken(&lookahead);
        } else error_expected(t);
    } else {
        if (!strcmp(lookahead.token_name,t)) {
            printToken(lookahead);
            getNextToken(&lookahead);
        } else error_expected(t);
    }
}

void expn(); void eprime();
void simple_expn(); void seprime();
void term(); void tprime();
void factor();

void expn() {
    simple_expn();
    eprime();
}

void eprime() {
    if (!strcmp(lookahead.token_name,"==") ||
        !strcmp(lookahead.token_name,"!=") ||
        !strcmp(lookahead.token_name,"<") ||
        !strcmp(lookahead.token_name,">") ||
        !strcmp(lookahead.token_name,"<=") ||
        !strcmp(lookahead.token_name,">=")) {
        match(lookahead.token_name);
        simple_expn();
    }
}

void simple_expn() {
    term();
    seprime();
}

void seprime() {
    if (!strcmp(lookahead.token_name,"+") ||
        !strcmp(lookahead.token_name,"-")) {
        match(lookahead.token_name);
        term();
        seprime();
    }
}

void term() {
    factor();
    tprime();
}

void tprime() {
    if (!strcmp(lookahead.token_name,"*") ||
        !strcmp(lookahead.token_name,"/") ||
        !strcmp(lookahead.token_name,"%")) {
        match(lookahead.token_name);
        factor();
        tprime();
    }
}

void factor() {
    if (!strcmp(lookahead.type,"id"))
        match("id");
    else if (!strcmp(lookahead.type,"num"))
        match("num");
    else
        error_expected("id or num");
}

void identifier_list() {
    match("id");

    if (!strcmp(lookahead.token_name,"[")) {
        match("[");
        match("num");
        match("]");
    }

    if (!strcmp(lookahead.token_name,",")) {
        match(",");
        identifier_list();
    }
}

void declarations() {
    if (!strcmp(lookahead.token_name,"int") ||
        !strcmp(lookahead.token_name,"char")) {
        match(lookahead.token_name);
        identifier_list();
        match(";");
        declarations();
    }
}

void assign_stat() {
    match("id");

    if (!strcmp(lookahead.token_name,"[")) {
        match("[");
        match("num");
        match("]");
    }

    match("=");
    expn();
    match(";");
}

void statement() {
    assign_stat();
}

void statement_list() {
    if (!strcmp(lookahead.type,"id")) {
        statement();
        statement_list();
    }
}

void program() {
    match("main");
    match("(");
    match(")");
    match("{");

    declarations();
    statement_list();

    match("}");
}

int main() {
    fp = stdin;

    if (!getNextToken(&lookahead)) {
        printf("Empty input\n");
        return 0;
    }

    program();

    if (error_count == 0)
        printf("Parsing successful\n");
    else
        printf("Parsing completed with %d error(s)\n", error_count);

    return 0;
}