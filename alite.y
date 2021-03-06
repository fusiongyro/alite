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
#include "symtable.h"

int yylex();
void yyerror(char*);
int yyparse();

#define NARITH(x,y,z) (make_arith_node(x,y,z))
#define NASSIGN(x,y)  (make_assignment_node(x,y))
#define NLIT(x)       (make_literal_node(x))
#define NVAR(x)       (make_variable_node(x))
#define NNEGATE(x)    (negate(x));

// symbol table
symtable_node_t* symbol_table = NULL;

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
%token IDENT
%token ASSIGN

%union {
  int value;
  int base;
  int expt;
  wchar_t* ident;
  struct node* node;
}

%type<value> INTEGER 
%type<base> BASE
%type<expt> EXPT
%type<ident> IDENT
%type<node> expression

%right ASSIGN
%left PLUS MINUS
%left TIMES DIVIDES
%left RAISED EXPT

%%

input : /* empty */ | input line;

line : NEWLINE 
  | expression NEWLINE             { eval_and_display($1); };

expression : INTEGER               { $$ = NLIT($1); }
  | INTEGER BASE                   { $$ = NLIT(baseconvert($1, $2)); }
  | IDENT                          { $$ = NVAR($1); }
  | LPAREN expression RPAREN       { $$ = $2; parenthesize($$); }
  | PLUS expression %prec TIMES    { $$ = $2; }
  | MINUS expression %prec TIMES   { $$ = NNEGATE($2); }
  | expression PLUS expression     { $$ = NARITH($1, PLUS, $3); }
  | expression MINUS expression    { $$ = NARITH($1, MINUS, $3); }
  | expression TIMES expression    { $$ = NARITH($1, TIMES, $3); }
  | expression DIVIDES expression  { $$ = NARITH($1, DIVIDES, $3); }
  | IDENT ASSIGN expression        { $$ = NASSIGN($1, $3); }
  | expression RAISED expression   { $$ = NARITH($1, RAISED, $3); }
  | expression EXPT                { $$ = NARITH($1, RAISED, NLIT($2)); };

%% 

void yyerror(char* s)
{
  printf("%s\n", s);
}

int main(int argc, char* argv[])
{
  symbol_table = make_symbol_table();
  setlocale(LC_ALL, "");
  yyparse();
}
