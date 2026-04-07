#include "token.h"
#include <stdlib.h>

int main() {
    FILE *fp = fopen("input.c","r");
    if (!fp) {
        printf("Cannot open file\n");
        return 0;
    }

    char c, lexeme[50];
    int idx = 0, index = 1;
    unsigned int row = 1, col = 0;

    struct token t;

    printf("TOKEN NAME\t\t TYPE\t\t ROW\t\t COL\n");
    printf("----------------------------------------------------------------------------\n");

    while ((c = fgetc(fp)) != EOF) {
        col++;

        if (c == '\n') {
            row++;
            col = 0;
            continue;
        }

        if (isspace(c))
            continue;

        idx = 0;

        if (isalpha(c) || c == '_') {
            lexeme[idx++] = c;
            while (isalnum(c = fgetc(fp)) || c == '_') {
                lexeme[idx++] = c;
                col++;
            }
            lexeme[idx] = '\0';
            ungetc(c, fp);

            strcpy(t.token_name, lexeme);
            t.row = row;
            t.col = col - strlen(lexeme) + 1;
            t.index = index++;

            if (isKeyword(lexeme))
                strcpy(t.type, "KEYWORD");
            else
                strcpy(t.type, "IDENTIFIER");
        }

        else if (isdigit(c)) {
            lexeme[idx++] = c;
            while (isdigit(c = fgetc(fp))) {
                lexeme[idx++] = c;
                col++;
            }
            lexeme[idx] = '\0';
            ungetc(c, fp);

            strcpy(t.token_name, lexeme);
            strcpy(t.type, "NUMERICAL CONSTANT");
            t.row = row;
            t.col = col - strlen(lexeme) + 1;
            t.index = index++;
        }

        else if (c == '"') {
            lexeme[idx++] = c;
            while ((c = fgetc(fp)) != '"') {
                lexeme[idx++] = c;
                col++;
            }
            lexeme[idx++] = '"';
            lexeme[idx] = '\0';

            strcpy(t.token_name, lexeme);
            strcpy(t.type, "STRING LITERAL");
            t.row = row;
            t.col = col - strlen(lexeme) + 1;
            t.index = index++;
        }

        else {
            lexeme[idx++] = c;
            char next = fgetc(fp);

            if (next == '=' || (c=='&' && next=='&') || (c=='|' && next=='|')) {
                lexeme[idx++] = next;
            } else {
                ungetc(next, fp);
            }

            lexeme[idx] = '\0';

            strcpy(t.token_name, lexeme);
            t.row = row;
            t.col = col;
            t.index = index++;

            if (isArithmetic(lexeme))
                strcpy(t.type,"ARITHMETIC OPERATOR");
            else if (isRelational(lexeme))
                strcpy(t.type,"RELATIONAL OPERATOR");
            else if (isLogical(lexeme))
                strcpy(t.type,"LOGICAL OPERATOR");
            else if (isSpecialSymbol(c))
                strcpy(t.type,"SPECIAL SYMBOL");
            else
                strcpy(t.type,"UNKNOWN");
        }

        printf("%s\t\t %s\t\t %d\t\t %d\n",
               t.token_name, t.type, t.row, t.col);
    }

    fclose(fp);
    return 0;
}
