/* CHISELITA Sebastian - 314CA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "stacks.h"

// deschide pagina cu id-ul dat
void open_page(browser *browse, page *pages, int nr_pages, int id, FILE *fout)
{
	page *new_page = NULL;
	tab *curr = browse->current_tab;

	for (int i = 0; i < nr_pages; i++) {
		if (pages[i].id == id) {
			new_page = &pages[i];
			break;
		}
	}

	// daca new_page e NULL, nu am gasit pagina
	if (!new_page) {
		fprintf(fout, "403 Forbidden\n");
		return;
	}

	if (curr->current_page)
		push(curr->backward_stack, curr->current_page);

	clear_stack(curr->forward_stack);
	curr->current_page = new_page;
}

void backward(browser *browse, FILE *fout)
{
	tab *curr = browse->current_tab;
	if (is_empty(curr->backward_stack)) {
		fprintf(fout, "403 Forbidden\n");
		return;
	}

	if (curr->current_page)
		push(curr->forward_stack, curr->current_page);

	page *prev_page = pop(curr->backward_stack);
	curr->current_page = prev_page;
}

void forward(browser *browse, FILE *fout)
{
	tab *curr = browse->current_tab;
	if (is_empty(curr->forward_stack)) {
		fprintf(fout, "403 Forbidden\n");
		return;
	}

	if (curr->current_page)
		push(curr->backward_stack, curr->current_page);

	page *next_page = pop(curr->forward_stack);
	curr->current_page = next_page;
}
