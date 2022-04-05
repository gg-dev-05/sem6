%{
#include<stdio.h> // for input
int flag=1;
%}

%%
A*B*        {flag=1;}
"\n"        {return 0;}
.           {flag=0;} 
%%

int yywrap(){
    return 1;
}

int main(void){
	extern FILE *yyin;
	yyin = fopen("input.in", "r");
    yylex();
    if(flag){
        printf("YES\n");
    }else{
        printf("NO\n");
    }
    return 0;
}