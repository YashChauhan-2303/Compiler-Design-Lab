%{
#include <stdio.h>
int vowel = 0;
int consonant = 0;
%}

%%
[aeiouAEIOU]    { vowel++; }
[a-zA-Z]        { consonant++; }
%%

int main()
{
    yylex();
    printf("Vowels = %d\nConsonants = %d\n", vowel, consonant);
    return 0;
}

int yywrap()
{
    return 1;
}
