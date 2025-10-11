/* CHISELITA Sebastian - 314CA */
#ifndef STRUCTS
#define STRUCTS

#include <stdio.h>

#define MAX_LINE 50

typedef struct {
	int id;
	char url[MAX_LINE];
	char *description;
} page;

typedef struct stack_node {
	page *pages;
	struct stack_node *next;
} stack_node;

typedef struct {
	struct stack_node *top;
} stack;

typedef struct {
	int id;
	page *current_page;
	stack *backward_stack;
	stack *forward_stack;
} tab;

typedef struct node {
	tab *tabs;
	struct node *prev;
	struct node *next;
} node;

typedef struct {
	node *sentinel;
} tab_list;

typedef struct {
	tab *current_tab;
	tab_list list;
} browser;

#endif
