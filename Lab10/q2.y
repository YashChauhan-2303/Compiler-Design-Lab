%{
    #include<stdio.h>
    #include<stdlib.h>

    int yylex(void);
    int yyerror(char *msg);
%}

%token IF ELSE ID NUMBER RELOP NL

%%
stmt : decision NL { printf("Valid Decision Statement\n"); exit(0); };

decision :
      IF '(' cond ')' decision
    | IF '(' cond ')' decision ELSE decision
    | ID ';'
    ;

cond :
      ID RELOP ID
    | ID RELOP NUMBER
    ;
%%

int yyerror(char *msg){
    printf("Invalid Decision Statement\n");
    exit(0);
}

int main(){
    printf("Enter the Decision Statement\n");
    yyparse();
    return 0;
}