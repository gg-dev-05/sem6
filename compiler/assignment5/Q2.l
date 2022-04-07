%{ 
#include <stdio.h> 
#include <string.h> 
int total_number_of_operators = 0, total_number_of_operands = 0, is_valid = 1;
int startsWithOperator = 0;
%}

%%
" " {}
"+"|"-"|"*"|"/" { 
  if(startsWithOperator == 0) {
    startsWithOperator = 2;
  }
  total_number_of_operators++; 
} 
[0-9]+|[a-zA-Z][a-zA-Z0-9_]* { 
  if(startsWithOperator == 0) {
    startsWithOperator = 1;
  }
  total_number_of_operands++; 
} 
"\n" {}
. { is_valid = 0; }
%% 
  
int yywrap() { 
  return 1; 
} 

int main() { 
	extern FILE *yyin;
	yyin = fopen("Q2.in", "r");
  yylex(); 
  if(is_valid == 1 && total_number_of_operands - total_number_of_operators == (startsWithOperator ? 1 : 0)){
      printf("The given expression is valid with %d operands and %d operators\n", total_number_of_operands, total_number_of_operators); 
  } else {
      printf("The given Expression is inis_valid\n"); 
  }
  return 0;
}