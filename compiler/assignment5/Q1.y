%{
  #include <stdio.h>
  #include <stdlib.h>
  int yylex();
  void yyerror(char *s);
  int valid=1;
%}

%token A B NL

%%
startSymbol: a b NL {printf("Valid Input\n");exit(0);};
a: {} | A a {} ;
b: {} | B b {} ;
%%

void yyerror(char *s){
  valid=0;
  printf("Invalid Input\n");
  exit(1);
}

int main(){
  printf("Enter Expression:\n");
  yyparse();
  return 0;
}