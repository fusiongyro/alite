%{

  /*
   * Grammar for alite
   * 
   * by Daniel Lyons <fusion@storytotell.org>
   *
   * License: MIT
   *
   * I'm not really sure where I'm going with this yet, but for now,
   * think of this as a sort of calculator that supports Unicode
   * operators. I intend to expand this into a fully Unicode
   * implementation of ALGOL 60, but I may go for something weirder;
   * we'll see.
   *
   */

#include <stdio.h>
#include <locale.h>
#include <math.h>

#include "util.h"
#include "ast.h"
#include "eval.h"

int yylex();
void yyerror(char*);
int yyparse();

#define ARITH(x,y,z) (make_arith_node(x,y,z))
#define LIT(x)       (make_literal_node(x))

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
  | expression NEWLINE       { eval_and_display($1); }

expression : term            { $$ = $1; }
  | PLUS term                { $$ = $2; }
  | MINUS term               { $$ = ARITH(LIT(0), MINUS, $2); }
  | expression PLUS term     { $$ = ARITH($1, PLUS, $3); }
  | expression MINUS term    { $$ = ARITH($1, MINUS, $3); };

primary : INTEGER            { $$ = LIT($1); }
  | INTEGER BASE             { $$ = LIT(baseconvert($1, $2)); }
  | LPAREN expression RPAREN { $$ = $2; parenthesize($$); };

factor : primary             { $$ = $1; }
  | factor RAISED primary    { $$ = ARITH($1, RAISED, $3); }
  | factor EXPT              { $$ = ARITH($1, RAISED, LIT($2)); };

term : factor                { $$ = $1; }
  | term TIMES factor        { $$ = ARITH($1, TIMES, $3); }
  | term DIVIDES factor      { $$ = ARITH($1, DIVIDES, $3); };

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
