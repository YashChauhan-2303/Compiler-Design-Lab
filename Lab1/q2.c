

#include <stdio.h>

int main() {

FILE *fp1, *fp2;

long size;

char ch;

fp1 = fopen("input.txt", "r");

fp2 = fopen("reverse.txt", "w");

if (fp1 == NULL || fp2 == NULL) {

printf("File error\n");

return 1;

}

fseek(fp1, 0, SEEK_END);

size = ftell(fp1);

printf("Size of file = %ld bytes\n", size);

for (long i = size - 1; i >= 0; i--) {

fseek(fp1, i, SEEK_SET);

ch = fgetc(fp1);

fputc(ch, fp2);

}

fclose(fp1);

fclose(fp2);

printf("File reversed successfully\n");

return 0;

} 