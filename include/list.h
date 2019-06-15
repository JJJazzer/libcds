/*
 * file name: list.h
 * author   : Yu Liu
 * email    : <ilhanwnz@hotmail.com>
 * time     : Fri 31 May 2019 06:34:52 PM CST
 */

#ifndef _LIST_H
#define _LIST_H

#include "types.h"


#define T	List_T
typedef struct T	*T;

/* DO NOT:
 * 	Do not call this function, please use macro "List()"
 * 	to create a link list.
 */
extern T list_constructor();

#define LIST_INIT(type) 		list_constructor(sizeof(type))

extern _Bool 	list_empty		(T lst);
extern int 	list_size		(T lst);
extern void 	list_pushback		(T lst, Generic x);
extern Generic 	list_popback 		(T lst);
extern void 	list_insert		(T lst, Generic x, int index);
extern Generic 	list_remove_by_idx	(T lst, int index);
extern void 	list_delete		(T *lst);
extern int 	list_find_elem 		(T lst, Generic x);
extern void 	list_walk		(T lst, int (*CALLBACK) (void*));

#undef T
#endif 
