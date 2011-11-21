	#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "pprint.h"

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

wchar_t digitToUnicodeSuperscript(int digit)
{
  switch (digit)
  {
    case 0: return L'⁰';    case 1: return L'¹';
    case 2: return L'²';    case 3: return L'³';
    case 4: return L'⁴';    case 5: return L'⁵';
    case 6: return L'⁶';    case 7: return L'⁷';
    case 8: return L'⁸';    case 9: return L'⁹';
    default: return -1;
  }
}


wchar_t* intToRaised(int number)
{
  size_t len = log10(number) + 1;
  wchar_t *result = malloc(sizeof(wchar_t) * len);
  int i = 0;

  for (int num = number; num > 0; num = num / 10)
    result[len-1-i++] = digitToUnicodeSuperscript(num % 10);

  result[i] = L'\0';
  
  return result;
}

void pprint_nice_exponent(node_t* left, int right)
{
  pprint_node(left);
  wchar_t *s = intToRaised(right);
  printf("%ls", s);
  free(s);
}

void pprint_arithmetic(arith_exp* node)
{
  if (node->op == EXP && node->right->type == LITERAL)
    pprint_nice_exponent(node->left, node->right->u.literal);

  else
  {
    printf("(");
    pprint_node(node->left);
    printf(" "); 
    pprint_op(node->op);
    printf(" ");
    pprint_node(node->right);
    printf(")");
  }
}

void pprint_node(node_t* node)
{
  switch (node->type)
  {
    case LITERAL:
      printf("%d", node->u.literal);
      break;
      
    case ARITHMETIC:
      pprint_arithmetic(&node->u.arithmetic);
      break;
  }
}
