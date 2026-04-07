%{
    #include "q4.tab.h"
%}

%%

[0-9]+ {return NUM;}

[ \t] ;

\n {return NL;}

[+\-*/^n] {return yytext[0];}

. {return yytext[0];}

%%

int yywrap(){
    return 1;
}