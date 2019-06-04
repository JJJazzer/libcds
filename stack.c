/*
 * file name: stack.c
 * author   : Yu Liu
 * email    : <ilhanwnz@hotmail.com>
 * time     : Tue 04 Jun 2019 08:26:29 AM CST
 */

#include "stack.h"
#include "chktools.h"
#include <assert.h>

struct elem {
	Generic x;
	struct elem *next;
};

_Bool stk_empty(stack stk);
int   stk_size (stack stk);
void  stk_push (stack stk, Generic x);
Generic stk_pop  (stack stk);
void  stk_delete(stack *stk);

#define stk_is_nil(expr)	\
	if ((expr) == (void*) 0)\
		exception_stack(NIL_PTR);

stack stack_constructor(int nbyte)
{
	stack stk;
	stk = chkmalloc(sizeof(*stk));
	stk->head = NULL;
	stk->length = 0;
	stk->head = NULL;
	stk->nbyte = nbyte;
	
	stk->empty = stk_empty;
	stk->size = stk_size;
	stk->push = stk_push;
	stk->pop = stk_pop;
	stk->delete = stk_delete;
	return stk;
}

_Bool stk_empty(stack stk)
{
	stk_is_nil(stk);
	return stk->length == 0;
}
int stk_size(stack stk)
{
	stk_is_nil(stk);
	return stk->length;
}
void stk_push(stack stk, Generic x)
{
	struct elem *t;
	stk_is_nil(stk);
	t = chkmalloc(sizeof(*t));
	t->x = x;
	t->next = stk->head;
	stk->head = t;
	stk->length++;
}

Generic stk_pop(stack stk)
{
	Generic x;
	struct elem *t;
	if (stk->length <= 0) { 
		exception_stack(ACC_OFLOW);
		return NULL;
	}
	stk_is_nil(stk);
	t = stk->head;
	stk->head = t->next;
	stk->length--;
	x = t->x;
	free(t);
	return x;
}

void stk_delete(stack *stk)
{
	struct elem *t, *u;
	for (t = (*stk)->head; t; t = u) {
		u = t->next;
		free(t);
	}
	free(*stk);
}
