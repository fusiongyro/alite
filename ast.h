#include "wchar.h"

typedef enum {
  ADD,
  SUB, 
  MUL, 
  DIV, 
  EXP
} mathop;

struct node;

typedef struct {
  struct node* left;
  mathop op;
  struct node* right;
} arith_exp;

typedef enum {
  ARITHMETIC,
  LITERAL
} node_type;

typedef struct node {
  node_type type;
  union {
    arith_exp arithmetic;
    int literal;
  } u;
} node_t;

node_t* make_arith_node(node_t* left, int op, node_t* right);
node_t* make_literal_node(int value);
void pprint_node(node_t* node);
int evaluate(node_t* node);
