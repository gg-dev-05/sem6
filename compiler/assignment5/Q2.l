%{ 
#include <stdio.h> 
#include <string.h> 
#define STACK_SIZE 500
char stack[STACK_SIZE]; 
int operator_counter = 0, operand_counter = 0, isValidExpression = 1, stackTop = -1; 
int overflow = 0;
%}

%%
"(" { 
    stackTop++; 
    if(stackTop == STACK_SIZE-1) overflow = 1;
    stack[stackTop] = '('; 
  } 
"[" { 
    stackTop++; 
    if(stackTop == STACK_SIZE-1) overflow = 1;
    stack[stackTop] = '['; 
  } 
")" { 
    if (stack[stackTop] != '(') { 
        isValidExpression = 0;     
    }
    else{
        stackTop--;
    } 
} 
"]" { 
    if (stack[stackTop] != '[') { 
        isValidExpression = 0; 
    }
    else{
        stackTop--;
    } 
          
} 
"+"|"-"|"*"|"/" {
    operator_counter++; 
} 
[0-9]+|[a-zA-Z][a-zA-Z0-9_]* { 
    operand_counter++; 
} 
%% 
  
int yywrap(){ 
    return 1; 
} 

int main(){ 
    extern FILE *yyin;
    yyin = fopen("input.in","r");
    yylex(); 
  
    // if expression is valid and stack is empty
    // and difference of operand_counter and operator_counter is exactly 1
    // => Expression is valid
    if (isValidExpression == 1 && stackTop == -1 && operand_counter - operator_counter == 1) { 
      printf("The given expression is valid and contains %d operands and %d operators\n", operand_counter, operator_counter);
    } 
    else{
      printf("Invalid Expression\n"); 
    }
    return 0;
} 