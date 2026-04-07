%{
#include <stdio.h>
int sc = 0, pr = 0;
%}

%%
scanf      { printf("READ"); sc++; }
printf     { printf("WRITE"); pr++; }
.|\n       { printf("%s", yytext); }
%%

int main()
{
    yylex();
    printf("\nScanf count = %d\nPrintf count = %d\n", sc, pr);
    return 0;
}

int yywrap()
{
    return 1;
}
