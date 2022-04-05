%{ 
#include <stdio.h> 
#include <string.h> 
int oprtr_count = 0, oprnd_count = 0, valid = 1, top = -1, l = 0, j = 0; 
char oprnd[10][10], oprtr[10][10], stack[100]; 
%}

%%
"(" { top++; stack[top] = '('; } 
"{" { top++; stack[top] = '{'; } 
"[" { top++; stack[top] = '['; } 
")" { 
    if (stack[top] != '(') { 
        valid = 0;     
    }
    else{
        top--;
    } 
} 
"}" { 
    if (stack[top] != '{') { 
        valid = 0;     
    }
    else{
        top--;
    } 
} 
"]" { 
    if (stack[top] != '[') { 
        valid = 0; 
    }
    else{
        top--;
    } 
          
} 
"+"|"-"|"*"|"/" { 
    oprtr_count++; 
    strcpy(oprtr[l], yytext);
    l++; 
} 
[0-9]+|[a-zA-Z][a-zA-Z0-9_]* { 
    oprnd_count++; 
    strcpy(oprnd[j], yytext); 
    j++; 
} 
%% 
  
int yywrap() 
{ 
    return 1; 
} 

int main() 
{ 
    extern FILE *yyin;
    yyin = fopen("input.txt","r");
    yylex(); 
  
    if (valid == 1 && top == -1 && oprnd_count - oprtr_count == 1) { 
        printf("Valid Expression\n\n"); 
        printf("Total operands = %d\n",oprnd_count);
        printf("Total operators = %d\n",oprtr_count);
    } 
    else
        printf("Invalid Expression\n"); 
  
    return 0;
} 