#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main() {
    int c;
    char buf[10];
    FILE *fp = fopen("q1_input.c", "r");

    if (fp == NULL) {
        printf("Can't open file!!");
        exit(0);
    }

    while ((c = fgetc(fp)) != EOF) {
        int i = 0;
        buf[0] = '\0';

        if (c == '=') {
            buf[i++] = c;
            c = fgetc(fp);

            if (c == '=') {
                buf[i++] = c;
                buf[i] = '\0';
                printf("\nRelational operator: %s", buf);
            } else {
                buf[i] = '\0';
                printf("\nAssignment operator: %s", buf);
                ungetc(c, fp);
            }
        }
        else if (c == '<' || c == '>' || c == '!') {
            buf[i++] = c;
            c = fgetc(fp);

            if (c == '=') {
                buf[i++] = c;
            } else {
                ungetc(c, fp);
            }

            buf[i] = '\0';

            if (strcmp(buf, "!") == 0)
                printf("\nLogical operator: %s", buf);
            else
                printf("\nRelational operator: %s", buf);
        }
    }

    fclose(fp);
    return 0;
}
