%{
  #include <stdio.h>
  #include "y.tab.h"
%}

%%
" " {}
[0-9]+|[a-zA-Z][a-zA-Z0-9_]*  {return NUMBER;}
"\n" return 0;
.    return yytext[0];
%%

int yywrap(){
  return 1;
}