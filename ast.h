#ifndef __AST_H_
#define __AST_H_

/*
 * Abstract syntax tree definitions
 */

#include <stdbool.h>

#include "wchar.h"

/* These are the arithmetic operators for the AST */
typedef enum {
  ADD,
  SUB, 
  MUL, 
  DIV, 
  EXP
} mathop;

struct node;

/* This is an arithmetic node */
typedef struct {
  struct node* left;
  mathop op;
  struct node* right;
} arith_exp;

typedef struct {
  wchar_t* identifier;
  struct node* value;
} ident_exp;

/* Node types currently supported */
typedef enum {
  ARITHMETIC,
  LITERAL,
  ASSIGNMENT,
  VARIABLE,
  NEGATE
} node_type;

/* The node type itself. It's a tagged union of different nodes. */
typedef struct node {
  node_type type;
  bool parenthesized;
  union {
    arith_exp arithmetic;
    int literal;
    ident_exp assignment;
    wchar_t* variable;
    struct node* negate;
  } u;
} node_t;

/* Functions for constructing different node types */
node_t* make_arith_node(node_t*, int op, node_t*);
node_t* make_literal_node(int);
node_t* make_assignment_node(wchar_t* ident, node_t* value);
node_t* make_variable_node(wchar_t* ident);
node_t* negate(node_t*);

/* Mark a node as parenthesized (for display later) */
void parenthesize(node_t* node);

#endif
