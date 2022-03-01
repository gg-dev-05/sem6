%{
    #include<stdio.h>
    int totalPrintStatements=0,totalScanStatements=0;
%}

%%
("printf") {totalPrintStatements++;}
("scanf") {totalScanStatements++;}
.       ;
%%

int yywrap(void){}

int main()
{   
    extern FILE* yyin;
    yyin = fopen("Q2.in","r");
    yylex();
    printf("Total number of printf statements:%d\nTotal number  of scanf statements:%d\n",totalPrintStatements,totalScanStatements);
    return 0;
}