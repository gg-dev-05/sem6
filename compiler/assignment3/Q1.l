%{
#include<stdio.h>
int words=0;
%}

%%
[ \n]                                     ; // ignore blank tabs and newlines
([a-zA-Z0-9]*[^a-zA-Z0-9 \n]+[^ \n]*)   ; // ignore words with special characters
[a-zA-Z0-9]*                                {words++;} // include words
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter input words: (Press Ctrl+d to exit)\n");
    yylex();
    printf("This file contains %d words\n", words);
}
