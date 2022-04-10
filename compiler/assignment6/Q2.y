%{
  #include <stdio.h>
  #include <stdlib.h>
  extern FILE *yyin;
  int valid=1;
  int yylex();
  void yyerror(char *s);
%}
  
%token OPEN_BRAKET1 OPEN_BRAKET2 CLOSE_BRAKET1 CLOSE_BRAKET2 TEXT		  

%%
/* Start symbol */
start : s
  ;
/* parenthesis symbol parenthesis */
s: x s x
 | x OPEN_BRAKET1 s CLOSE_BRAKET1 x  /* { text } */
 | x OPEN_BRAKET2 s CLOSE_BRAKET2 x  /* ( text ) */
 |
  ;
x: TEXT s
 |	            
  ;
%%
  
void yyerror(char *s){
   printf("Parenthesis are not balanced\n");
   exit(1);
}
  
int main(){
   /* Read from input.c file */
  char file[] = "input.c";
  yyin = fopen(file , "r");
  yyparse();
  /* Will execute only if no errors are detected */
  printf("Parenthesis are balanced\n");
}
