%{
    #include "q1.tab.h"
%}

%%
int|float|char|double {return TYPE;}
[a-zA-Z][a-zA-Z0-9_]* {return ID;}
"," {return COMMA;}
";" {return SEMICOLON;}
[ \t\n] ; 
. {return yytext[0];}
%%

int yywrap(){
    return 1;
}