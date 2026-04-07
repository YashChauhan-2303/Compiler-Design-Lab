#include <stdio.h>
#include <string.h>
#include <ctype.h>
const char *keywords[] = {
"int", "char", "float", "double", "if", "else", "while", "for",
"return", "break", "continue", "long", "short", "unsigned", "signed"
};
int isKeyword(char *word) {
int n = sizeof(keywords) / sizeof(keywords[0]);
for (int i = 0; i < n; i++) {
if (strcmp(word, keywords[i]) == 0)
return 1;
}
return 0;
}
void toUpperCase(char *word) {
for (int i = 0; word[i]; i++)
word[i] = toupper(word[i]);
}
int main() {
FILE *fp1 = fopen("q3_input.c", "r");
FILE *fp2 = fopen("output.c", "w");
if (fp1 == NULL || fp2 == NULL) {
printf("Error opening file\n");
return 1;
}
char ch, word[100];
int i = 0;
while ((ch = fgetc(fp1)) != EOF) {
if (isalnum(ch) || ch == '_') {
word[i++] = ch;
} else {
if (i > 0) {
word[i] = '\0';
if (isKeyword(word)) {
toUpperCase(word);
}
fputs(word, fp2);
i = 0;
}
fputc(ch, fp2);
}
}
if (i > 0) {
word[i] = '\0';
if (isKeyword(word)) {
toUpperCase(word);
}
fputs(word, fp2);
}
fclose(fp1);
fclose(fp2);
printf("Keywords converted successfully.\n");
return 0;
} 