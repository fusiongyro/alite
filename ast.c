#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "y.tab.h"
#include "ast.h"

/*
 * AST generating functions
 */

/* make an arithmetic node */
node_t* make_arith_node(node_t* left, int op, node_t* right)
{
  node_t* result = malloc(sizeof(node_t));
  
  result->type = ARITHMETIC;
  result->u.arithmetic.left = left;
  result->u.arithmetic.right = right;
  result->parenthesized = false;
  
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

/* Make a literal node */
node_t* make_literal_node(int value)
{
  node_t* result = malloc(sizeof(node_t));
  result->type = LITERAL;
  result->u.literal = value;
  result->parenthesized = false;
  return result;
}

/* Make an assignment node */
node_t* make_assignment_node(wchar_t* identifier, node_t* value)
{
  node_t* result = malloc(sizeof(node_t));
  result->type = ASSIGNMENT;
  result->u.assignment.identifier = identifier;
  result->u.assignment.value = value;
  result->parenthesized = false;
  return result;
}

/* Make a variable reference node */
node_t* make_variable_node(wchar_t* ident)
{
  node_t* result = malloc(sizeof(node_t));
  result->type = VARIABLE;
  result->u.variable = ident;
  result->parenthesized = false;
  return result;
}

node_t* negate(node_t* node)
{
  node_t* result = node;

  if (node->type == LITERAL)
    node->u.literal = -node->u.literal;
  else
  {
    result = malloc(sizeof(node_t));
    result->type = NEGATE;
    result->u.negate = node;
    result->parenthesized = false;
  }

  return result;
}
  

/* Mark a node as parenthesized */
void parenthesize(node_t* node)
{
  node->parenthesized = true;
}
