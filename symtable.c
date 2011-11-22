#include <stdlib.h>
#include <stdio.h>
#include "symtable.h"

symtable_node_t* make_symbol_table()
{
  symtable_node_t* result = malloc(sizeof(symtable_node_t));
  result->next = NULL;
  return result;
}

void add_symbol(symtable_node_t* table, wchar_t* symbol, int value)
{
  for (; table->next != NULL; table = table->next)
  {
    if (!wcscmp(table->symbol, symbol))
    {
      table->value = value;
      return;
    }
  }

  table->next = make_symbol_table();
  table->symbol = symbol;
  table->value = value;
}

int lookup(symtable_node_t* table, wchar_t* symbol)
{
  for (; table != NULL && table->symbol != NULL && wcscmp(table->symbol, symbol); table = table->next);
  return (table != NULL) ? table->value : 0;
}
