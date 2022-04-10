%{
#include<stdio.h>
#include "y.tab.h"
extern int result;
%}
%%
[0-9]+ { yylval=atoi(yytext); return NUMBER;}; // Return NUMBER token for all numbers and convert from str to int
[ \t] {;} // Ignore Tabs and white spaces
[\n] return 0; // end on newlines
. return yytext[0]; // other characters
%%

int yywrap()
{
return 1;
}
