%{
#include <stdio.h>
%}

%%
"//".*           { printf("%s", yytext); }
"/*"([^*]|\*+[^*/])*\*+"/" { printf("%s", yytext); }
[A-Z]            { printf("%c", yytext[0] + 32); }
.|\n             { printf("%s", yytext); }
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
