%{
	int comments = 0;
	int temp = 0;
	int singleLine = 0;
%}

%%
"//".*         {if(temp==0){singleLine++;comments++;}}
"/*"           {if(temp==0)temp=1;}
.              ; 
"\n"           ; 
"*/"           {if(temp==1){temp=0;comments++;}}
%%

int yywrap(){}
int main(int argc, char **argv)
{
	/* read input from Q2.txt */
	extern FILE *yyin;
	yyin = fopen("Q2.txt", "r");
	printf("\nReading from Q2.txt\n");
	yylex();
	printf("\nSingle Line comments: %d\n",singleLine);
	printf("\nMulti Line comments: %d\n",comments-singleLine);
}