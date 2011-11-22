#include <stdio.h>
#include <math.h>

#include "pprint.h"
#include "eval.h"
#include "symtable.h"

/*
 * Evaluation methods
 */

extern symtable_node_t* symbol_table;

/* evaluate an arithmetic expression */
int evaluate_arithmetic(arith_exp* arith)
{
  switch (arith->op)
  {
    case ADD:  return evaluate(arith->left) + evaluate(arith->right);
    case SUB:  return evaluate(arith->left) - evaluate(arith->right);
    case MUL:  return evaluate(arith->left) * evaluate(arith->right);
    case DIV:  return evaluate(arith->left) / evaluate(arith->right);
    case EXP:
      return pow(evaluate(arith->left), evaluate(arith->right));
  }

  printf("falling out of case in evaluate_arithmetic\n");
  return 0;
}

/* Gateway method: evaluate a node */
int evaluate(node_t* node)
{
  int val = 0;

  switch (node->type)
  {
    case LITERAL:
      val = node->u.literal; 
      break;
 
    case ARITHMETIC:
      val = evaluate_arithmetic(&node->u.arithmetic);
      break;

    case ASSIGNMENT:
      val = evaluate(node->u.assignment.value);
      add_symbol(symbol_table, node->u.assignment.identifier, val);
      break;

    case VARIABLE:
      val = lookup(symbol_table, node->u.variable);
      break;
  }

  return val;
}

/* Gateway method: pretty print the node and then evaluate it. */
void eval_and_display(node_t* node)
{
  pprint_node(node);
  printf(" = %d\n", evaluate(node));
}
