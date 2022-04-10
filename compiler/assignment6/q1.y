%{
/* Definition section */
	#include<stdio.h>
	#include <stdlib.h>
  int yylex();
  void yyerror(char *s);
%}

%token NUMBER
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

/* Rule Section */
%%
/* Start Symbol */
Result: E{printf("\nResult=%d\n", $$);return 0;}
	;
E: E'+'E {$$=$1+$3;}
	|E'-'E {$$=$1-$3;}
	|E'*'E {$$=$1*$3;}
	|E'%'E {$$=$1%$3;}
	|'('E')' {$$=$2;}
	| NUMBER {$$=$1;}
;
%%

void main(){
	printf("Enter any arithemetic expression (+,-,*,%%,(,)):");
	yyparse();
}

void yyerror(char *s){
	printf("Invalid Expression\n");
	exit(1);
}
