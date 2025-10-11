/* CHISELITA Sebastian - 314CA */
#ifndef TABS
#define TABS

#include "structs.h"
#include "stacks.h"

tab * create_tab(int id, page * first_page);

tab_list create_list(void);

void add_new_tab(tab_list *list, tab *new_tab);

void new_tab(browser *browse, page *first_page, int *next_id);

void remove_tab(tab_list *list, node *tab_node);

void close_tab(browser *browse, FILE *fout);

void open_tab(browser *browse, int id, FILE *fout);

#endif
