#include <stdio.h>

int main() {
    FILE *fp1, *fp2, *fp3;
    char line1[100], line2[100];

    fp1 = fopen("file1.txt", "r");
    fp2 = fopen("file2.txt", "r");
    fp3 = fopen("result.txt", "w");

    if (fp1 == NULL || fp2 == NULL || fp3 == NULL) {
        printf("File error\n");
        return 1;
    }

    while (1) {
        int r1 = fgets(line1, sizeof(line1), fp1) != NULL;
        int r2 = fgets(line2, sizeof(line2), fp2) != NULL;

        if (!r1 && !r2)
            break;

        if (r1)
            fputs(line1, fp3);

        if (r2)
            fputs(line2, fp3);
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    printf("Files merged alternatively\n");
    return 0;
}
