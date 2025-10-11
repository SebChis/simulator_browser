/* CHISELITA Sebastian - 314CA */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "stacks.h"
#include "tabs.h"
#include "move_tabs.h"
#include "pages.h"
#include "prints.h"
#include "frees.h"

#define MAX_LINE 50

void init_browser(browser *br, page **default_page, int *next_id)
{
	br->list = create_list();

	*default_page = malloc(sizeof(page));
	if (!*default_page) {
		fprintf(stderr, "Error 1\n");
		exit(1);
	}

	(*default_page)->id = 0;
	strcpy((*default_page)->url, "https://acs.pub.ro/");
	(*default_page)->description = strdup("Computer Science");
	if (!(*default_page)->description) {
		fprintf(stderr, "Error 2\n");
		exit(1);
	}

	// initializam tab-ul default cu id egal cu 0
	new_tab(br, *default_page, next_id);
}

// citim si salvam elementele distincte pentru paginile web
page *read_pages(FILE *fin, int nr_pages)
{
	page *pages = malloc(nr_pages * sizeof(page));
	if (!pages) {
		fprintf(stderr, "Error 3\n");
		exit(1);
	}

	for (int i = 0; i < nr_pages; i++) {
		fscanf(fin, "%d\n", &pages[i].id);
		fgets(pages[i].url, MAX_LINE, fin);
		pages[i].url[strcspn(pages[i].url, "\n")] = 0;

		char buffer[MAX_LINE];
		fgets(buffer, MAX_LINE, fin);
		buffer[strcspn(buffer, "\n")] = 0;

		pages[i].description = malloc(strlen(buffer) + 1);
		if (!pages[i].description) {
			fprintf(stderr, "Error 4\n");
			exit(1);
		}
		strcpy(pages[i].description, buffer);
	}

	return pages;
}

int main(void)
{
	FILE *fin = fopen("tema1.in", "r");
	FILE *fout = fopen("tema1.out", "w");

	browser browse;
	int next_tab_id = 0;
	page *default_page = NULL;
	init_browser(&browse, &default_page, &next_tab_id);

	int nr_pages;
	fscanf(fin, "%d\n", &nr_pages);

	page *pages = read_pages(fin, nr_pages);

	int nr_operations;
	fscanf(fin, "%d\n", &nr_operations);

	char operation[MAX_LINE];
	for (int i = 0; i < nr_operations; i++) {
		fgets(operation, MAX_LINE, fin);
		operation[strcspn(operation, "\n")] = 0;

		// verificam ce operatie avem de facut
		if (strcmp(operation, "NEW_TAB") == 0) {
			page *copy_page = malloc(sizeof(page));
			if (!copy_page) {
				fprintf(stderr, "Error 5\n");
				return 1;
			}

			copy_page->id = 0;
			strcpy(copy_page->url, default_page->url);
			copy_page->description = strdup(default_page->description);
			new_tab(&browse, copy_page, &next_tab_id);
		} else if (strcmp(operation, "CLOSE") == 0) {
			close_tab(&browse, fout);
		} else if (strncmp(operation, "OPEN", 4) == 0) {
			int id = atoi(operation + 5);
			open_tab(&browse, id, fout);
		} else if (strcmp(operation, "NEXT") == 0) {
			next_tab(&browse);
		} else if (strcmp(operation, "PREV") == 0) {
			prev_tab(&browse);
		} else if (strncmp(operation, "PAGE", 4) == 0) {
			int id = atoi(operation + 5);
			open_page(&browse, pages, nr_pages, id, fout);
		} else if (strcmp(operation, "BACKWARD") == 0) {
			backward(&browse, fout);
		} else if (strcmp(operation, "FORWARD") == 0) {
			forward(&browse, fout);
		} else if (strcmp(operation, "PRINT") == 0) {
			print_tabs(&browse, fout);
		} else if (strncmp(operation, "PRINT_HISTORY", 13) == 0) {
			int id = atoi(operation + 14);
			print_history(&browse, id, fout);
		} else {
			fprintf(stderr, "Error 6\n");
		}
	}

	// eliberam ce memorie a mai ramas si inchidem fisierele
	free_browser(&browse);
	for (int i = 0; i < nr_pages; i++)
		free(pages[i].description);

	free(pages);

	fclose(fin);
	fclose(fout);

	return 0;
}
