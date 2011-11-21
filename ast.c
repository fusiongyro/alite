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

    default:
      printf("No op assigned!\n");
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
