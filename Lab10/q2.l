%{
    #include "q2.tab.h"
%}

%%
if {return IF;}
else {return ELSE;}
[0-9]+ {return NUMBER;}
[a-zA-Z][a-zA-Z0-9_]* {return ID;}
"=="|"<="|">="|"!="|"<"|">" {return RELOP;}

[ \t] ;          /* ignore spaces and tabs */

\n {return NL;}

. {return yytext[0];}
%%

int yywrap(){
    return 1;
}