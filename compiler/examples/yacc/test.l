%{
  #include "y.tab.h"
  int yylex();
  void yyerror(char *s);
%}

%%
("hi"|"oi")"\n" {return HI;}
("tchau"|"bye")"\n" {return BYE;}
. {yyerror("Unknown character");}
%%

int yywrap(void){
  return 0;
}