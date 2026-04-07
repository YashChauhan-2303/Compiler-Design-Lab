%{
#include <stdio.h>
int pos_int = 0, neg_int = 0;
int pos_float = 0, neg_float = 0;
%}

%%
[+]?[0-9]+                { pos_int++; }
-[0-9]+                  { neg_int++; }
[+]?[0-9]*\.[0-9]+        { pos_float++; }
-[0-9]*\.[0-9]+           { neg_float++; }
%%

int main()
{
    yylex();
    printf("Positive Integers = %d\n", pos_int);
    printf("Negative Integers = %d\n", neg_int);
    printf("Positive Floats   = %d\n", pos_float);
    printf("Negative Floats   = %d\n", neg_float);
    return 0;
}

int yywrap()
{
    return 1;
}
