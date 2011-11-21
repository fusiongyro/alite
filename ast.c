#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "y.tab.h"
#include "ast.h"

node_t* make_arith_node(node_t* left, int op, node_t* right)
{
  node_t* result = malloc(sizeof(node_t));
  
  result->type = ARITHMETIC;
  result->u.arithmetic.left = left;
  result->u.arithmetic.right = right;
  
  switch (op)
  {
    case PLUS: 
      result->u.arithmetic.op = ADD;
      break;

    case MINUS:
      result->u.arithmetic.op = SUB;
      break;
      
    case TIMES:
      result->u.arithmetic.op = MUL;
      break;

    case DIVIDES:
      result->u.arithmetic.op = DIV;
      break;

    case RAISED:
      result->u.arithmetic.op = EXP;
      break;
  }

  return result;
}

node_t* make_literal_node(int value)
{
  node_t* result = malloc(sizeof(node_t));
  result->type = LITERAL;
  result->u.literal = value;
  return result;
}

void pprint_node(node_t* node)
{
  switch (node->type)
  {
    case LITERAL:
      printf("%d", node->u.literal);
      break;
      
    case ARITHMETIC:
      pprint_node(node->u.arithmetic.left);
      printf(" <%d> ", node->u.arithmetic.op);
      pprint_node(node->u.arithmetic.right);
      break;
  }
}

int evaluate_arithmetic(arith_exp* arith)
{
  switch (arith->op)
  {
    case ADD:
      return evaluate(arith->left) + evaluate(arith->right);
      
    case SUB:
      return evaluate(arith->left) - evaluate(arith->right);

    case MUL:
      return evaluate(arith->left) * evaluate(arith->right);

    case DIV:
      return evaluate(arith->left) / evaluate(arith->right);

    case EXP:
      return pow(evaluate(arith->left), evaluate(arith->right));
  }

  return 0;
}

int evaluate(node_t* node)
{
  switch (node->type)
  {
    case LITERAL:
      return node->u.literal;
      break;
      
    case ARITHMETIC:
      return evaluate_arithmetic(&node->u.arithmetic);
      break;
  }

  return 0;
}
