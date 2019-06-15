/*
 * file name: stack.h
 * author   : Yu Liu
 * email    : <ilhanwnz@hotmail.com>
 * time     : Tue 04 Jun 2019 08:08:00 AM CST
 */

#ifndef _STACK_H
#define _STACK_H

#include "types.h"

#define T 	Stack_T
typedef struct T 	*T; 

extern T stack_constructor(int nbyte);
#define STACK_INIT(type) 		stack_constructor(sizeof(type))
extern _Bool 	stack_empty 		(T stk);
extern int 	stack_size 		(T stk);
extern void 	stack_push 		(T stk, Generic x);
extern void    *stack_pop 		(T stk);
extern void 	stack_delete		(T *stk);
#undef T

#endif
