%{
#include <stdio.h>
#include <stdlib.h>
%}

%%
[0-9]+ {
    int n = atoi(yytext);
    printf("Hexadecimal = %X\n", n);
}
%%

int main()
{
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}
