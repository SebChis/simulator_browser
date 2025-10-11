/* CHISELITA Sebastian - 314CA */
#ifndef STACKS
#define STACKS

#include "structs.h"

stack * create_stack();

void push(stack *st, page *pag);

page *pop(stack *st);

int is_empty(stack *st);

void clear_stack(stack *st);

void free_page_id_zero(stack *st);

#endif
