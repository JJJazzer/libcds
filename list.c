/*
 * file name: list.c
 * author   : Yu Liu
 * email    : <ilhanwnz@hotmail.com>
 * time     : Sat 01 Jun 2019 07:56:44 PM CST
 */

#include "list.h"
#include "chktools.h"
#include <assert.h>
#include <string.h>

struct list_info {
	int len;
	int nbyte;
};

struct elem {
	Generic x;
	struct elem *next;
};
_Bool list_empty(list_ptr lst);
int   list_size(list_ptr);
void  list_push_back(list_ptr lst, Generic x);
Generic list_pop_back(list_ptr lst);
void  list_insert(list_ptr lst, Generic x, int index);
Generic list_remove_by_index(list_ptr lst, int index);
void  list_delete(list_ptr *lst);
int   list_find_elem(list_ptr lst, Generic x);
void  list_walk(list_ptr lst, int (*func)());

#define list_is_nil(expr)	\
	if ((expr) == 0)       \
		exception_list(NIL_PTR)

list list_constructor(int nbyte)
{
 	list t;
	t = chkmalloc(sizeof(*t));
	t->l_info = chkmalloc(sizeof(*t->l_info));
	t->head = chkmalloc(sizeof(*t->head));
	t->l_info->len = 0;
	t->l_info->nbyte = nbyte;

	t->empty = list_empty;
	t->size  = list_size;
	t->push_back = list_push_back;
	t->pop_back = list_pop_back;
	t->insert = list_insert;
	t->remove_by_index = list_remove_by_index;
	t->delete = list_delete;
	t->find_elem = list_find_elem;
	t->walk = list_walk;
	return t;
}

_Bool list_empty(list_ptr lst)
{
	list_is_nil(lst && lst->head);
	return lst->l_info->len == 0;
}

int list_size(list_ptr lst)
{
	list_is_nil(lst && lst->head);
	return lst->l_info->len;
}

#define goto_list_tail(cur, points, len)\
	struct elem *cur; 		\
	cur = points; 		\
	for (int i = 0; i < len; i++)	\
		cur = cur->next;	\

void list_push_back(list_ptr lst, Generic x)
{
	list_is_nil(lst && lst->head);
	list_insert(lst, x, lst->l_info->len);
}

Generic list_pop_back(list_ptr lst)
{
	list_is_nil(lst && lst->head);
	return list_remove_by_index(lst, lst->l_info->len);
}

void list_insert(list_ptr lst, Generic x, int index)
{
	struct elem *t;
	t = chkmalloc(sizeof(*t));
	goto_list_tail(cur, lst->head, index);
	t->x = x;
	t->next = cur->next;
	cur->next = t;
	lst->l_info->len++;
}

Generic list_remove_by_index(list_ptr lst, int index)
{
	Generic x;
	struct elem *tmpnode;
	list_is_nil(lst && lst->head);
	if (index < 0 || index > lst->l_info->len) {
		exception_list(ACC_OFLOW);
		return NULL;
	}
	goto_list_tail(cur, lst->head, index - 1);
	x = cur->next->x;
	tmpnode = cur->next;
	cur->next = tmpnode->next;
	free(tmpnode);
	lst->l_info->len--;
	return x;
}

void list_delete(list_ptr *lst)
{
	list_is_nil(lst && *lst);
	struct elem *t, *u;
	for (t = (*lst)->head; t; t = u) {
		u = t->next;
		free(t);
	}
	free(*lst);
}

int list_find_elem(list_ptr lst, Generic x)
{
	list_is_nil(lst && lst->head);
	struct elem *cur = lst->head->next;
	int index = 0;
	while (cur != NULL) {
		if (memcmp(cur->x, x, lst->l_info->nbyte) == 0)
			return index;
		index++;
		cur = cur->next;
	}
	return -1;
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
	list_is_nil(lst && lst->head);
	struct elem *cur = lst->head->next;
	walk_list(cur, func(cur->x));
}
