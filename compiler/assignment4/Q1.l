%{
    #include<stdio.h>
    int randomNum; 
    void smallLetter(char *word){
        int curr=yytext[0]-'a';
        curr = (curr+randomNum)%26;
        char ch = 'a'+ curr;
        fprintf(yyout,"%c",ch);
        randomNum++;
    }
    void capitalLetter(char *word){
        int curr = yytext[0]-'A';
        curr = (curr+randomNum)%26;
        char ch = 'A'+ curr;
        fprintf(yyout,"%c",ch);
        randomNum++;
    }
%}

%%
([a-z]) {smallLetter(yytext);}
([A-Z]) {capitalLetter(yytext);}
(\n)    ; 
.       ; 
%%

int yywrap(void){}

int main()
{   
    extern FILE* yyin,*yyout;
    yyin = fopen("Q1.in","r");
    yyout = fopen("Q1.out","w");
    /* Assign random number to shift */
    randomNum = 4;
    yylex();
    return 0;
}