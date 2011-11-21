#include <stdio.h>
#include <math.h>

#include "eval.h"

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
