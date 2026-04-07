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
            t->row = row;
            t->col = col;
            i = 0;

            t->token_name[i++] = '"';

            while ((c = fgetc(fp)) != '"' && c != EOF) {
                if (c == '\n') {
                    row++;
                    col = 0;
                }
                t->token_name[i++] = c;
            }

            t->token_name[i++] = '"';
            t->token_name[i] = '\0';

            strcpy(t->type, "STRING LITERAL");
            return 1;
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

            strcpy(t->type, "NUMERICAL CONSTANT");
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
    fp = fopen("test.c", "r");
    if (!fp) {
        printf("Cannot open file\n"); return 0;
    }
    int row = 1;
        while (getNextToken(&t)) {
            if (strcmp(t.type, "IDENTIFIER") == 0)
                printf("<id,%d,%d> ", t.row, t.col);
            else if (strcmp(t.type, "NUMERICAL CONSTANT") == 0)
                printf("<num,%d,%d> ", t.row, t.col);
            else if (strcmp(t.type, "KEYWORD") == 0)
                printf("<%s,%d,%d> ", t.token_name, t.row, t.col);
            else if (strcmp(t.type, "ARITHMETIC OPERATOR") == 0 || strcmp(t.type, "RELATIONAL OPERATOR") == 0 || strcmp(t.type, "LOGICAL OPERATOR") == 0 || strcmp(t.type, "SPECIAL SYMBOL") == 0
            )
                printf("<%s,%d,%d> ", t.token_name, t.row, t.col);
            else if (strcmp(t.type, "STRING LITERAL") == 0)
                printf("<string,%d,%d> ", t.row, t.col);
    }
    printf("\n"); 
    fclose(fp); 
    return 0;
} 
