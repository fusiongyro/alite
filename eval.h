#ifndef __EVAL_H_
#define __EVAL_H_

/*
 * Evaluation facility.
 */

#include "ast.h"

int evaluate(node_t*);
void eval_and_display(node_t*);

#endif
