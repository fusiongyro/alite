%{

#include <stdio.h>
#include <locale.h>
#include <math.h>

int yylex();
void yyerror(char*);

%}

%token INTEGER
%token PLUS
%token MINUS
%token TIMES
%token DIVIDES
%token RAISED
%token NEWLINE

%%

input : /* empty */ | input line;

line : NEWLINE 
  | expression NEWLINE { printf("%d\n", $1); }

expression : term         { $$ = $1; }
  | PLUS term             { $$ = $2; }
  | MINUS term            { $$ = -$2; }
  | expression PLUS term  { $$ = $1 + $3; }
  | expression MINUS term { $$ = $1 - $3; };

primary : INTEGER         { $$ = $1; };

factor : primary          { $$ = $1; }
  | factor RAISED primary { $$ = pow($1, $3); };

term : factor             { $$ = $1; }
  | term TIMES factor     { printf("I've got %d %d %d\n", $1, $2, $3); $$ = $1 * $3; }
  | term DIVIDES factor   { $$ = $1 / $3; };

%% 

void yyerror(char* s)
{
  printf("%s\n", s);
}

int main(int argc, char* argv[])
{
  setlocale(LC_ALL, "");
  yyparse();
}