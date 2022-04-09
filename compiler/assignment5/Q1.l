%{
  #include <stdio.h>
  #include "y.tab.h"
%}

%%
[aA]  return A;
[bB]  return B;
\n    return NL;
.     return yytext[0];
%%

int yywrap(void){
  return 1;
}