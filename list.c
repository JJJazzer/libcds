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

#define T	List_T
struct T {
	struct elem {
		Generic x;
		struct elem *next;
	} *head;
	int length;
	int nbyte;
};

_Bool 	list_empty		(T lst);
int   	list_size		(T lst);
void 	list_pushback		(T lst, Generic x);
Generic list_popback		(T lst);
void  	list_insert		(T lst, Generic x, int index);
Generic list_remove_by_idx	(T lst, int index);
void  	list_delete		(T *lst);
int     list_find_elem		(T lst, Generic x);
Generic list_get_elem_by_idx	(T lst, int index);
void  	list_walk		(T lst, int (*CALLBACK)(void*));

#define list_is_nil(expr)	\
	if ((expr) == 0)       \
		exception_list(NIL_PTR)

T list_constructor(int nbyte)
{
 	T t;
	t = chkmalloc(sizeof(*t));
	t->head = chkmalloc(sizeof(*(t->head)));
	t->length = 0;
	t->nbyte = nbyte;
	return t;
}

_Bool list_empty(T lst)
{
	list_is_nil(lst);
	return lst->length == 0;
}

int list_size(T lst)
{
	list_is_nil(lst);
	return lst->length;
}

#define goto_list_tail(cur, points, length)\
	struct elem *cur; 		\
	cur = points; 		\
	for (int i = 0; i < length; i++)	\
		cur = cur->next;	\

void list_pushback(T lst, Generic x)
{
	list_is_nil(lst);
	list_insert(lst, x, lst->length);
}

Generic list_popback(T lst)
{
	list_is_nil(lst && lst->length);
	return list_remove_by_idx(lst, lst->length - 1);
}

void list_insert(T lst, Generic x, int index)
{
	struct elem *t;
	t = chkmalloc(sizeof(*t));
	goto_list_tail(cur, lst->head, index);
	t->x = x;
	t->next = cur->next;
	cur->next = t;
	lst->length++;
}

Generic list_remove_by_idx(T lst, int index)
{
	Generic x;
	struct elem *tmpnode;
	list_is_nil(lst && lst->length);
	if (index < 0 || index > lst->length) {
		exception_list(ACC_OFLOW);
		return NULL;
	}
	goto_list_tail(cur, lst->head, index);
	x = cur->next->x;
	tmpnode = cur->next;
	cur->next = tmpnode->next;
	free(tmpnode);
	lst->length--;
	return x;
}

void list_delete(T *lst)
{
	list_is_nil(lst && *lst);
	struct elem *t, *u;
	for (t = (*lst)->head; t; t = u) {
		u = t->next;
		free(t);
	}
	free(*lst);
}

int list_find_elem(T lst, Generic x)
{
	list_is_nil(lst && lst->length);
	struct elem *cur = lst->head->next;
	int index = 0;

	while (cur != NULL) {
		if (cur->x == x)
			return index;
		index++;
		cur = cur->next;
	}
	return -1;
}

Generic list_get_elem_by_idx(T lst, int index)
{	
	list_is_nil(lst && lst->length);
	goto_list_tail(cur, lst->head, index);
	return cur->next->x;
}
#define walk_list(cur, func)	\
{						\
	while (cur != NULL) { 			\
		func; 				\
		cur = cur->next; 		\
	}					\
}
void list_walk(T lst, int (*CALLBACK)(void*))
{
	list_is_nil(lst);
	struct elem *cur = lst->head->next;
	walk_list(cur, CALLBACK(cur->x));
}
