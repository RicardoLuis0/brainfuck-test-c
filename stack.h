#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <stdint.h>

#include "bool.h"

typedef struct _uint32_t_stack uint32_t_stack;
uint32_t_stack * make_stack();
void free_stack(uint32_t_stack*);
bool pop(uint32_t_stack*);
bool push(uint32_t_stack*,uint32_t);
uint32_t peek(uint32_t_stack*);

#endif // STACK_H_INCLUDED
