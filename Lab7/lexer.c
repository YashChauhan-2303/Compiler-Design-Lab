#include "token.h"
#include <stdlib.h>

FILE *fp;
unsigned int row = 1, col = 0;

char *keywords[] = {
    "int","float","char","double","void",
    "if","else","while","for","return"
};
int keywordCount = 10;

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
            ch==';'||ch==','||ch=='['||ch==']');
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
            char buf[20];
            int i = 0;

            while ((c = fgetc(fp)) != '\n' && c != EOF && i < 19)
                buf[i++] = c;
            buf[i] = '\0';

            row++;
            col = 0;

            if (strcmp(buf, "include") == 0)
                continue;

            printf("Error at row %u, column %u: invalid preprocessor directive #%s\n",
                    row - 1, 1, buf);
            exit(1);
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
                strcpy(t->type, "id");

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

            strcpy(t->type, "num");
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

// int main() {
//     struct token t;
//     fp = fopen("test.c", "r");
//     if (!fp) {
//         printf("Cannot open file\n"); return 0;
//     }
//     int row = 1;
//         while (getNextToken(&t)) {
//             if (strcmp(t.type, "IDENTIFIER") == 0)
//                 printf("<id,%d,%d> ", t.row, t.col);
//             else if (strcmp(t.type, "NUMERICAL CONSTANT") == 0)
//                 printf("<num,%d,%d> ", t.row, t.col);
//             else if (strcmp(t.type, "KEYWORD") == 0)
//                 printf("<%s,%d,%d> ", t.token_name, t.row, t.col);
//             else if (strcmp(t.type, "ARITHMETIC OPERATOR") == 0 || strcmp(t.type, "RELATIONAL OPERATOR") == 0 || strcmp(t.type, "LOGICAL OPERATOR") == 0 || strcmp(t.type, "SPECIAL SYMBOL") == 0
//             )
//                 printf("<%s,%d,%d> ", t.token_name, t.row, t.col);
//             else if (strcmp(t.type, "STRING LITERAL") == 0)
//                 printf("<string,%d,%d> ", t.row, t.col);
//     }
//     printf("\n"); 
//     fclose(fp); 
//     return 0;
// } 
