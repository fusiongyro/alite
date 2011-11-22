#ifndef __SYMTABLE_H_
#define __SYMTABLE_H_

#include <wchar.h>

typedef struct symtable_node_s {
  wchar_t* symbol;
  int value;
  struct symtable_node_s* next;
} symtable_node_t;

symtable_node_t* make_symbol_table();
void add_symbol(symtable_node_t*, wchar_t* symbol, int value);
int lookup(symtable_node_t*, wchar_t* symbol);

#endif
