/*
 * file name: stack.h
 * author   : Yu Liu
 * email    : <ilhanwnz@hotmail.com>
 * time     : Tue 04 Jun 2019 08:08:00 AM CST
 */

#ifndef _STACK_H
#define _STACK_H

#include "types.h"

typedef struct stack *stack; 

struct stack {
	struct elem *head;
	int 	length;
	int 	nbyte;
	_Bool	(*empty)	(stack stk);
	int	(*size)		(stack stk);
	void 	(*push)		(stack stk, Generic x);
	void* 	(*pop) 		(stack stk);
	void 	(*delete) 	(stack *stk);
};

extern stack stack_constructor(int nbyte);
#define Stack(type) 		stack_constructor(sizeof(type))
#endif
