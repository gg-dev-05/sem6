%{ 
   /* Definition section */
   #include<stdio.h>
  #include "y.tab.h" 
%}
/* Rule Section */
%% 
[aA] { 
	// printf("a");
	return A;} 
[bB] {
	// printf("b");
	return B;
	} 
\n 	 {return NL;} 
.  	 {return yytext[0];} 
%%   
int yywrap()  
{  
	return 1;  
}