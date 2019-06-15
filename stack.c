/*
 * file name: T.c
 * author   : Yu Liu
 * email    : <ilhanwnz@hotmail.com>
 * time     : Tue 04 Jun 2019 08:26:29 AM CST
 */

#include "stack.h"
#include "chktools.h"
#include <assert.h>

#define T 	Stack_T
struct T {
	struct elem {
		Generic x;
		struct elem *next;
	}*head;
	int 	length;
	int 	nbyte;
};

_Bool stack_empty		(T stack);
int   stack_size 		(T stack);
void  stack_push 		(T stack, Generic x);
Generic stack_pop 		(T stack);
void  stack_delete		(T *stack);

#define stack_is_nil(expr)	\
	if ((expr) == (void*) 0)\
		exception_stack(NIL_PTR);

T stack_constructor(int nbyte)
{
	T stack;
	stack = chkmalloc(sizeof(*stack));
	stack->head = NULL;
	stack->length = 0;
	stack->nbyte = nbyte;
	
	return stack;
}

_Bool stack_empty(T stack)
{
	stack_is_nil(stack);
	return stack->length == 0;
}
int stack_size(T stack)
{
	stack_is_nil(stack);
	return stack->length;
}
void stack_push(T stack, Generic x)
{
	struct elem *t;
	stack_is_nil(stack);
	t = chkmalloc(sizeof(*t));
	t->x = x;
	t->next = stack->head;
	stack->head = t;
	stack->length++;
}

Generic stack_pop(T stack)
{
	Generic x;
	struct elem *t;
	if (stack->length <= 0) { 
		exception_stack(ACC_OFLOW);
		return NULL;
	}
	stack_is_nil(stack);
	t = stack->head;
	stack->head = t->next;
	stack->length--;
	x = t->x;
	free(t);
	return x;
}

void stack_delete(T *stack)
{
	struct elem *t, *u;
	for (t = (*stack)->head; t; t = u) {
		u = t->next;
		free(t);
	}
	free(*stack);
}
