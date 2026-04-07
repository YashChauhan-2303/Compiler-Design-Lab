%{
    #include<stdio.h>
    #include<stdlib.h>

    int yylex(void);
    int yyerror(char *msg);
%}

%token NUMBER NL
%left '+''-'
%left '*''/'

%%
stmt : exp NL {printf("Result = %d\n",$1);exit(0);};

exp : exp '+' exp {$$=$1+$3;}
    | exp '-' exp {$$=$1-$3;}
    | exp '*' exp {$$=$1*$3;}
    | exp '/' exp {$$=$1/$3;}
    | NUMBER {$$=$1;}
    ;
%%

int yyerror(char *msg){
    printf("Invalid Expression\n");
    exit(0);
}

int main(){
    printf("Enter the Expression\n");
    yyparse();
    return 0;
}