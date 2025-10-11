/* CHISELITA Sebastian - 314CA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void print_tabs(browser *browse, FILE *fout)
{
	tab *curr = browse->current_tab;
	node *senti = browse->list.sentinel;
	node *iter = senti->next;

	while (iter != senti && iter->tabs != curr)
		iter = iter->next;

	if (iter == senti) {
		fprintf(stderr, "Error 14\n");
		return;
	}

	// afisam id-urile tab-urilor incepand cu cel de la pagina curenta
	node *stop = iter;
	do {
		fprintf(fout, "%d ", iter->tabs->id);
		iter = iter->next;
		if (iter == senti)
			iter = iter->next;
	} while (iter != stop);

	fprintf(fout, "\n");
	fprintf(fout, "%s\n", curr->current_page->description);
}

void print_history(browser *browse, int id, FILE *fout)
{
	node *senti = browse->list.sentinel;
	node *iter = senti->next;

	tab *find_tab = NULL;
	while (iter != senti) {
		if (iter->tabs->id == id) {
			find_tab = iter->tabs;
			break;
		}
		iter = iter->next;
	}

	if (!find_tab) {
		fprintf(fout, "403 Forbidden\n");
		return;
	}

	// facem o copie a stivei cu elementele in ordine inversa
	// pentru a afisa forward_stack de la primul element adaugat

	stack_node * temp = NULL;
	stack_node *iter_stack = find_tab->forward_stack->top;

	while (iter_stack) {
		stack_node *copy = malloc(sizeof(stack_node));
		if (!copy) {
			fprintf(stderr, "Error 15\n");
			return;
		}
		copy->pages = iter_stack->pages;
		copy->next = temp;
		temp = copy;
		iter_stack = iter_stack->next;
	}

	while (temp) {
		fprintf(fout, "%s\n", temp->pages->url);
		stack_node *aux = temp;
		temp = temp->next;
		free(aux);
	}

	// afisam pagina curenta
	fprintf(fout, "%s\n", find_tab->current_page->url);

	// afisam backward_stack de la ultimul element adaugat
	iter_stack = find_tab->backward_stack->top;
	while (iter_stack) {
		fprintf(fout, "%s\n", iter_stack->pages->url);
		iter_stack = iter_stack->next;
	}
}
