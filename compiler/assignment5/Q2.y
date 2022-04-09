%{
    #include<stdio.h>
	int yyerror();
    int valid=1;   
	int countOperands=0,countOperator=0;
%}


%token NUMBER
  
%left '+' '-'
  
%left '*' '/' '%'
  
%left '(' ')'

%%

ArithmeticExpression: E{
						return 0;				
						};
E:  E '+' E {countOperator++;}
	|E '-' E {countOperator++;}
	|E '*' E {countOperator++;}
	|E '/' E {countOperator++;}
	|E '%' E {countOperator++;}
 	| '(' E ')' {}
 	| NUMBER {countOperands++;} 
	;

%%

int yyerror()

{
	// if(!token) ignore
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
		printf("No. of operands-> %d\n",countOperands);
		printf("No. of operators-> %d\n",countOperator);

    }

}