%{
%}
%%
[\t ]+                   /* ignore whitespaces and tabs */ ;
am |
is |
are | 
was | 
were |
being |
been |
be |
have |
has |
had |
do |
does |
did |
will |
would |
shall |
should |
may |
might |
must |
can |
could        { printf("%s: is a helping verb\n", yytext); }
[a-zA-Z]+ { printf("%s: is not a helping verb\n", yytext); }
\n     {return 0;}
.      {;}
%%

int yywrap(){
    return 1;
}

int main(){
    yylex();
}