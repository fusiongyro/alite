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

void pprint_op(int op)
{
  switch (op)
  {
    case ADD: printf("+"); return;
    case SUB: printf("-"); return;
    case DIV: printf("/"); return;
    case MUL: printf("*"); return;
    case EXP: printf("^"); return;
  }

  printf("?");
}

void pprint_node(node_t* node)
{
  switch (node->type)
  {
    case LITERAL:
      printf("%d", node->u.literal);
      break;
      
    case ARITHMETIC:
      printf("(");
      pprint_node(node->u.arithmetic.left);
      printf(" "); 
      pprint_op(node->u.arithmetic.op);
      printf(" ");
      pprint_node(node->u.arithmetic.right);
      printf(")");
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

  printf("falling out of case in evaluate_arithmetic\n");
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

  printf("falling out of case in evaluate\n");
  return 0;
}

void eval_and_display(node_t* node)
{
  pprint_node(node);
  printf(" = %d\n", evaluate(node));
}
