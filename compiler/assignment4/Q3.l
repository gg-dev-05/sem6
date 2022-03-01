%{
    #include<stdio.h>
    int positiveIntegers=0,negativeIntegers=0,positiveFraction=0,negativeFraction=0;
%}

%%
[+]?[0-9]+ {positiveIntegers++;}
[-][0-9]+ {negativeIntegers++;}
[+]?[0-9]+[/.][0-9]+ {positiveFraction++;}
[-][0-9]+[/.][0-9]+ {negativeFraction++;}
[0-9]+[/.][-][0-9]+ {negativeFraction++;}
[-][0-9]+[/.][-][0-9]+ {positiveFraction++;}
.|\n {}
%%

int yywrap(void){
    return 1;
}

int main()
{   
    extern FILE* yyin;
    yyin = fopen("Q3.in","r");
    yylex();
    printf("Total number of positive integers: %d\nTotal number of negative integers: %d\nTotal number of positive fractions: %d\nTotal number of negative fractions: %d\n",positiveIntegers,negativeIntegers,positiveFraction,negativeFraction);
    return 0;
}