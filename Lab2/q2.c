#include<stdio.h>
#include<stdlib.h>
#include <string.h>

int main(){
    FILE *fa,*fb;
    int ca, cb;
    char word[50];
    fa = fopen("input.c","r");
    if(fa==NULL){
        printf("Cannot open file.\n");
        exit(0);
    }
    fb = fopen("output.c","w");
    ca = getc(fa);
    while(ca != EOF){
        if(ca == '#'){
            int i=0;
            word[i++]='#';
            ca = getc(fa);
            while(ca != EOF || ca != '\n' && i<49){
                word[i++] = ca;
                if(ca==' '|| ca=='\t') break;
                ca = getc(fa);
            }
            word[i]='\0';
            if (strncmp(word, "#include", 8) == 0 || strncmp(word, "#define", 7) == 0) {
                while (ca != EOF && ca != '\n') { 
                    ca = getc(fa);
                }
                if (ca == '\n') putc('\n', fb);
            } else {
                fputs(word, fb); 
                while (ca != EOF && ca != '\n') { 
                    putc(ca, fb); 
                    ca = getc(fa); 
                } 
                if (ca == '\n') putc('\n', fb);
            }
        } else {
            putc(ca,fb);
        }
        ca = getc(fa);
    }
    printf("Preprocessor directives from given C file reomved\n");
    fclose(fa);
    fclose(fb);
    return 0;
}