/* CHISELITA Sebastian - 314CA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

stack *create_stack(void)
{
	stack *st = malloc(sizeof(stack));
	if (!st) {
		fprintf(stderr, "Error 12\n");
		exit(1);
	}

	st->top = NULL;
	return st;
}

void push(stack *st, page *pag)
{
	stack_node *new_node = malloc(sizeof(stack_node));
	if (!new_node) {
		fprintf(stderr, "Error 13\n");
		exit(1);
	}

	new_node->pages = pag;
	new_node->next = st->top;
	st->top = new_node;
}

page *pop(stack *st)
{
	if (!st->top) {
		fprintf(stderr, "Error 14\n");
		return NULL;
	}

	stack_node *temp = st->top;
	page *pag = temp->pages;
	st->top = st->top->next;
	free(temp);
	return pag;
}

int is_empty(stack *st)
{
	return (!st || !st->top) ? 1 : 0;
}

void clear_stack(stack *st)
{
	while (!(is_empty(st))) {
		stack_node *temp = st->top;
		st->top = st->top->next;

		free(temp);
	}
}

// elibereaza o pagina doar daca are id-ul egal cu 0
void free_page_id_zero(stack *st)
{
	stack_node *iter = st->top;
	while (iter) {
		if (iter->pages && iter->pages->id == 0) {
			free(iter->pages->description);
			free(iter->pages);
			iter->pages = NULL;
		}
		iter = iter->next;
	}
}
