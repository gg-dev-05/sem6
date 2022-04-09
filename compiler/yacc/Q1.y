/* Yacc part*/
%{

    #include<stdio.h>

    int valid=1;   

%}

%token a b NL

%%
S : A B NL {printf("\n\n\t\tvalid string\n");
              exit(0); }
;

A :   {}
    | a A    {}
    ;
B :  {}
    | b B    {}
    ;

%%

int yyerror()

{

    valid=0;

    printf("\nInvalid expression!\n");

    return 0;

}

int main()

{

    printf("\nEnter the expression:\n");

    yyparse();

    if(valid)

    {

        printf("\nValid expression!\n");

    }

}