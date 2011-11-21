%{

#include <stdio.h>
#include <locale.h>
#include <math.h>

#include "util.h"
#include "ast.h"

int yylex();
void yyerror(char*);
int yyparse();

%}

%token INTEGER
%token PLUS
%token MINUS
%token TIMES
%token DIVIDES
%token RAISED
%token NEWLINE
%token BASE
%token EXPT
%token LPAREN
%token RPAREN

%union {
  int value;
  int base;
  int expt;
  struct node* node;
}

%type<value> INTEGER 
%type<base> BASE
%type<expt> EXPT
%type<node> expression term factor primary

%%

input : /* empty */ | input line;

line : NEWLINE 
  | expression NEWLINE    { eval_and_display($1); }

expression : term         { $$ = $1; }
  | PLUS term             { $$ = $2; }
  | MINUS term            { $$ = make_arith_node(make_literal_node(0), MINUS, $2); }
  | expression PLUS term  { $$ = make_arith_node($1, PLUS, $3); }
  | expression MINUS term { $$ = make_arith_node($1, MINUS, $3); };

primary : INTEGER         { $$ = make_literal_node($1); }
  | INTEGER BASE          { $$ = make_literal_node(baseconvert($1, $2)); }
  | LPAREN expression RPAREN { $$ = $2; parenthesize($$); };

factor : primary          { $$ = $1; }
  | factor RAISED primary { $$ = make_arith_node($1, RAISED, $3); }
  | factor EXPT           { $$ = make_arith_node($1, RAISED, make_literal_node($2)); };

term : factor             { $$ = $1; }
  | term TIMES factor     { $$ = make_arith_node($1, TIMES, $3); }
  | term DIVIDES factor   { $$ = make_arith_node($1, DIVIDES, $3); };

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
