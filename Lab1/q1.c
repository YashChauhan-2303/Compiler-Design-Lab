#include <stdio.h>
int main() {
    FILE *fp;
    char ch;
    int lines = 0, characters = 0;
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Cannot open file\n");
        return 1;
    }
    while ((ch = fgetc(fp)) != EOF) {
        characters++;
        if (ch == '\n')
        lines++;
    }
    fclose(fp);
    printf("Number of lines = %d\n", lines);
    printf("Number of characters = %d\n", characters);
    return 0;
} 