/* CHISELITA Sebastian - 314CA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "stacks.h"

tab *create_tab(int id, page *first_page)
{
	tab *new_tab = malloc(sizeof(tab));
	if (!new_tab) {
		fprintf(stderr, "Error 7\n");
		exit(1);
	}

	new_tab->id = id;
	new_tab->current_page = first_page;
	new_tab->backward_stack = create_stack();
	new_tab->forward_stack = create_stack();
	return new_tab;
}

// creaza lista de tab-uri a browser-ului
tab_list create_list(void)
{
	tab_list list;
	list.sentinel = malloc(sizeof(node));
	if (!list.sentinel) {
		fprintf(stderr, "Error 8\n");
		exit(1);
	}

	list.sentinel->tabs = NULL;
	list.sentinel->prev = list.sentinel;
	list.sentinel->next = list.sentinel;
	return list;
}

void add_new_tab(tab_list *list, tab *new_tab)
{
	node *new_node = malloc(sizeof(node));
	if (!new_node) {
		fprintf(stderr, "Error 9\n");
		exit(1);
	}

	new_node->tabs = new_tab;
	new_node->prev = list->sentinel->prev;
	new_node->next = list->sentinel;
	list->sentinel->prev->next = new_node;
	list->sentinel->prev = new_node;
}

void new_tab(browser *browse, page *first_page, int *next_id)
{
	tab *new_tab = create_tab((*next_id)++, first_page);
	add_new_tab(&browse->list, new_tab);
	browse->current_tab = new_tab;
}

void remove_tab(tab_list *list, node *tab_node)
{
	if (!tab_node || tab_node == list->sentinel) {
		fprintf(stderr, "Error 10\n");
		return;
	}

	tab_node->prev->next = tab_node->next;
	tab_node->next->prev = tab_node->prev;

	// eliberam stivele de pagini
	free_page_id_zero(tab_node->tabs->backward_stack);
	clear_stack(tab_node->tabs->backward_stack);
	free(tab_node->tabs->backward_stack);

	free_page_id_zero(tab_node->tabs->forward_stack);
	clear_stack(tab_node->tabs->forward_stack);
	free(tab_node->tabs->forward_stack);

	// eliberam pagina curenta daca are id-ul 0
	if (tab_node->tabs->current_page && tab_node->tabs->current_page->id == 0) {
		free(tab_node->tabs->current_page->description);
		free(tab_node->tabs->current_page);
		tab_node->tabs->current_page = NULL;
	}

	free(tab_node->tabs);
	free(tab_node);
}

void close_tab(browser *browse, FILE *fout)
{
	tab *curr = browse->current_tab;
	node *senti = browse->list.sentinel;
	node *iter = senti->next;

	if (curr->id == 0) {
		fprintf(fout, "403 Forbidden\n");
		return;
	}

	while (iter != senti) {
		// daca ambele indica catre acelasi tab
		if (iter->tabs == curr)
			break;
		iter = iter->next;
	}

	if (iter == senti || iter->prev == senti) {
		fprintf(stderr, "Error 11\n");
		return;
	}

	browse->current_tab = iter->prev->tabs;

	remove_tab(&browse->list, iter);
}

// seteaza tab-ul curent al browser-ului
void open_tab(browser *browse, int id, FILE *fout)
{
	node *senti = browse->list.sentinel;
	node *iter = senti->next;

	while (iter != senti) {
		if (iter->tabs->id == id) {
			browse->current_tab = iter->tabs;
			return;
		}
		iter = iter->next;
	}
	fprintf(fout, "403 Forbidden\n");
}
