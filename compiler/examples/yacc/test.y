%{
  #include <stdio.h>
  #include <stdlib.h>
  int yylex();
  void yyerror(char *s);
%}

%token HI BYE

%%
/* Start Symbol */
program: 
  hi bye
  ;
hi: HI {printf("HELLO WORLD\n");}
  ;
bye:
  BYE {printf("BYE WORLD\n");exit(0);}
  ;
%%

void main(){
  yyparse();
}

void yyerror(char *s){
  fprintf(stderr, "%s\n", s);
  exit(1);
}