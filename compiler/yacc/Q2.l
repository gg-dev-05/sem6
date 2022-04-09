%{ 
#include <stdio.h> 
#include <string.h> 

  #include "y.tab.h"
	// int countOperator=0,countOperands=0;
%}

%%
" " {}
[0-9]+|[a-zA-Z][a-zA-Z0-9_]* {
    return NUMBER;
} 

"\n" {return 0;}
. {return yytext[0];}

%% 
  
int yywrap() 
{ 
    return 1; 
} 