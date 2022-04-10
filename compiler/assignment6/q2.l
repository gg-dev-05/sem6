%{
  #include "y.tab.h"
%}
%%
"{" {return OPEN_BRAKET1;}
"(" {return OPEN_BRAKET2;}	
"}" {return CLOSE_BRAKET1;}	
")" {return CLOSE_BRAKET2;}
"\n" ;
.  {return TEXT;}
%%
int yywrap() {
  return 1; 
} 
