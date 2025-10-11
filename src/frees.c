/* CHISELITA Sebastian - 314CA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "stacks.h"

void free_browser(browser *browse)
{
	node *senti = browse->list.sentinel;
	node *iter = senti->next;

	while (iter != senti) {
		node *copy = iter->next;
		tab *temp = iter->tabs;

		// daca avem pagina cu id = 0 intr-o stiva, o eliberam
		free_page_id_zero(temp->backward_stack);
		free_page_id_zero(temp->forward_stack);
		clear_stack(temp->backward_stack);
		clear_stack(temp->forward_stack);
		free(temp->backward_stack);
		free(temp->forward_stack);

		// eliberam pagina curenta daca are id-ul egal cu 0
		if (temp->current_page && temp->current_page->id == 0) {
			free(temp->current_page->description);
			free(temp->current_page);
			temp->current_page = NULL;
		}

		// eliberam tab-ul si nodul sau
		free(temp);
		free(iter);
		iter = copy;
	}
	free(senti);
}
