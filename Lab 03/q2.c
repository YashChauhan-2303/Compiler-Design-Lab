#include "token.h"
#include <stdlib.h>

FILE *fp;
unsigned int row = 1, col = 0;

int getNextToken(struct token *t) {
    char c, next;
    int i = 0;

    while ((c = fgetc(fp)) != EOF) {
        col++;

        if (c == '\n') {
            row++;
            col = 0;
            continue;
        }

        if (isspace(c))
            continue;

        if (c == '#') {
            while ((c = fgetc(fp)) != '\n' && c != EOF);
            row++;
            col = 0;
            continue;
        }

        if (c == '/') {
            next = fgetc(fp);
            if (next == '/') {
                while ((c = fgetc(fp)) != '\n' && c != EOF);
                row++;
                col = 0;
                continue;
            }
            else if (next == '*') {
                while (1) {
                    c = fgetc(fp);
                    if (c == '\n') {
                        row++;
                        col = 0;
                    }
                    if (c == '*' && (next = fgetc(fp)) == '/')
                        break;
                }
                continue;
            } else {
                ungetc(next, fp);
            }
        }

        if (c == '"') {
            while ((c = fgetc(fp)) != '"' && c != EOF) {
                if (c == '\n') {
                    row++;
                    col = 0;
                }
            }
            continue;
        }

        if (isalpha(c) || c == '_') {
            t->row = row;
            t->col = col;
            t->token_name[i++] = c;

            while (isalnum(c = fgetc(fp)) || c == '_') {
                t->token_name[i++] = c;
                col++;
            }
            t->token_name[i] = '\0';
            ungetc(c, fp);

            if (isKeyword(t->token_name))
                strcpy(t->type, "KEYWORD");
            else
                strcpy(t->type, "IDENTIFIER");

            return 1;
        }

        if (isdigit(c)) {
            t->row = row;
            t->col = col;
            t->token_name[i++] = c;

            while (isdigit(c = fgetc(fp))) {
                t->token_name[i++] = c;
                col++;
            }
            t->token_name[i] = '\0';
            ungetc(c, fp);

            strcpy(t->type, "NUMERIC CONSTANT");
            return 1;
        }

        t->row = row;
        t->col = col;
        t->token_name[i++] = c;

        next = fgetc(fp);
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
        else if (isLogical(t->token_name))
            strcpy(t->type, "LOGICAL OPERATOR");
        else if (isSpecialSymbol(c))
            strcpy(t->type, "SPECIAL SYMBOL");
        else
            strcpy(t->type, "UNKNOWN");

        return 1;
    }
    return 0;
}

int main() {
    struct token t;
    fp = fopen("q1_input.c", "r");

    if (!fp) {
        printf("Cannot open file\n");
        return 0;
    }

    printf("TOKEN_NAME\t\tTYPE\t\t\tROW\tCOL\n");
    printf("--------------------------------------------------\n");

    while (getNextToken(&t)) {
        printf("%-12s %-22s %d\t%d\n",
               t.token_name, t.type, t.row, t.col);
    }

    fclose(fp);
    return 0;
}
