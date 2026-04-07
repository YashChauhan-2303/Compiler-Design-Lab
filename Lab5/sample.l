%{
    int chars = 0;
    int words = 0;
    int lines = 0;
%}

%%
[a-zA-Z]+ {words++;chars+=strlen(yytext);}
\n {chars++;lines++;}
. {chars++;}
%%

int main(){
    yylex();
    printf("Lines--->%d\nWords--->%d\nChars--->%d\n",lines,words,chars);
    }
    int yywrap()
    {
        return 1;
    }