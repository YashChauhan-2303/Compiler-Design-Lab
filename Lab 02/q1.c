#include <stdio.h>

int main() {
    FILE *fp1, *fp2;
    char ch;
    int space = 0;

    fp1 = fopen("input.txt", "r");
    fp2 = fopen("output.txt", "w");

    if (fp1 == NULL || fp2 == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while ((ch = fgetc(fp1)) != EOF) {
        if (ch == ' ' || ch == '\t') {
            if (!space) {
                fputc(' ', fp2);
                space = 1;
            }
        } else {
            fputc(ch, fp2);
            space = 0;
        }
    }

    fclose(fp1);
    fclose(fp2);

    printf("File processed successfully.\n");
    return 0;
}
