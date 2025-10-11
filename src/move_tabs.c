/* CHISELITA Sebastian - 314CA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void next_tab(browser *browse)
{
	node *senti = browse->list.sentinel;
	node *iter = senti->next;

	while (iter != senti) {
		if (iter->tabs == browse->current_tab) {
			if (iter->next != senti)
				browse->current_tab = iter->next->tabs;
			else
				browse->current_tab = senti->next->tabs;
			return;
		}
		iter = iter->next;
	}
}

void prev_tab(browser *browse)
{
	node *senti = browse->list.sentinel;
	node *iter = senti->next;

	while (iter != senti) {
		if (iter->tabs == browse->current_tab) {
			if (iter->prev != senti)
				browse->current_tab = iter->prev->tabs;
			else
				browse->current_tab = senti->prev->tabs;
			return;
		}
		iter = iter->next;
	}
}
