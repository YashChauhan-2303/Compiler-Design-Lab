%{
    #include<stdio.h>
    #include<stdlib.h>

    int yylex(void);
    int yyerror(char *msg);
%}

%token NUM NL

%%

input : line {exit(0);};

line : exp NL {printf("Valid Postfix Expression\n");};

exp : NUM
    | exp exp '+'
    | exp exp '-'
    | exp exp '*'
    | exp exp '/'
    | exp exp '^'
    | exp 'n'
    ;

%%

int yyerror(char *msg){
    printf("Invalid Postfix Expression\n");
    exit(0);
}

int main(){
    printf("Enter Postfix Expression\n");
    yyparse();
    return 0;
}