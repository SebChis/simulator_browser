/* CHISELITA Sebastian - 314CA */
#ifndef PAGES
#define PAGES

#include "structs.h"
#include "stacks.h"

void open_page(browser * br, page * pages, int nr_pages, int id, FILE * fout);

void backward(browser *browse, FILE *fout);

void forward(browser *browse, FILE *fout);

#endif
