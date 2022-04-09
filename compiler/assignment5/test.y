%{
  #include <stdio.h>
  int yyerror();
  int yylex();
  int valid=1;
  int operandCount=0, operatorCount=0;
%}

%token NUMBER

%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%%
E:  E '+' E {operatorCount++;}
  |E '-' E {operatorCount++;}
  |E '*' E {operatorCount++;}
  |E '/' E {operatorCount++;}
  |E '%' E {operatorCount++;}
  |'(' E ')' {};
  | NUMBER {operandCount++;}
%%

int yyerror(){
  printf("Invalid Expression\n");
  return 1;
}

int main(){
  printf("Enter Expression:\n");
  yyparse();
  printf("Operators: %d\nOperands: %d\n", operatorCount, operandCount);
}