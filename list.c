/*
 * file name: list.c
 * author   : Yu Liu
 * email    : <ilhanwnz@hotmail.com>
 * time     : Sat 01 Jun 2019 07:56:44 PM CST
 */

#include "list.h"
#include "chktools.h"
#include <assert.h>

struct list_info {
	int len;
};

struct elem {
	void *x;
	struct elem *next;
};
_Bool list_empty(list_ptr lst);
int   list_size(list_ptr);
void  list_push_back(list_ptr lst, void *x);
void *list_pop_back(list_ptr lst);
void  list_walk(list_ptr lst, int (*func)());

list list_constructor()
{
 	list t;
	t = chkmalloc(sizeof(*t));
	t->l_info = chkmalloc(sizeof(*t->l_info));
	t->head = chkmalloc(sizeof(*t->head));
	t->l_info->len = 0;
	t->empty = list_empty;
	t->size  = list_size;
	t->push_back = list_push_back;
	t->pop_back = list_pop_back;
	t->walk = list_walk;
	return t;
}

_Bool list_empty(list_ptr lst)
{
	return lst->l_info->len == 0;
}

int list_size(list_ptr lst)
{
	return lst->l_info->len;
}

#define goto_list_tail(cur, len) 	\
{					\
	for (int i = 0; i < len; i++)	\
		cur = cur->next;	\
}

void list_push_back(list_ptr lst, void *x)
{
	struct elem *t;
	t = chkmalloc(sizeof(*t));
	struct elem *cur;
	cur = lst->head;
	goto_list_tail(cur, lst->l_info->len);
	t->x = x;
	t->next = cur->next;
	cur->next = t;
	lst->l_info->len++;
}

void *list_pop_back(list_ptr lst)
{
	struct elem *cur;
	void *x;
	cur = lst->head;
	goto_list_tail(cur, lst->l_info->len - 1);
	x = cur->next->x;
	cur->next = NULL;
	free(cur->next);
	lst->l_info->len--;
	return x;
}

#define walk_list(cur, func)	\
{						\
	while (cur != NULL) { 			\
		func; 				\
		cur = cur->next; 		\
	}					\
}
void list_walk(list_ptr lst, int (*func)())
{
	struct elem *cur = lst->head->next;
	walk_list(cur, func(cur->x));
}
