%{
    #include<stdio.h>
    #include<stdlib.h>

    int yylex(void);
    int yyerror(char *msg);
%}

%token TYPE ID COMMA SEMICOLON NL

%%
stmt : decl {printf("Valid Declaration\n");exit(0);};

decl : TYPE list SEMICOLON;

list : list COMMA ID
     | ID;
%%

int yyerror(char *msg){
    printf("Invalid Declaration\n");
    exit(0);
}

int main(){
    printf("Enter the Declaration\n");
    yyparse();
    return 0;
}