/*
 * file name: list.h
 * author   : Yu Liu
 * email    : <ilhanwnz@hotmail.com>
 * time     : Fri 31 May 2019 06:34:52 PM CST
 */

#ifndef _LIST_H
#define _LIST_H

#include "types.h"

typedef struct list *list_ptr;
typedef struct list_info *list_info;

struct list {
	struct elem *head;
	int 	length;
	int 	nbyte;
	_Bool   (*empty) 	(list_ptr lst);
	int     (*size) 	(list_ptr lst);
	void    (*push_back)	(list_ptr lst, Generic x);
	Generic (*pop_back) 	(list_ptr lst);
	void    (*insert)	(list_ptr lst, Generic x, int index);
	Generic (*remove_by_index) (list_ptr lst, int index);
	void    (*delete) 	(list_ptr *lst);
	int     (*find_elem) 	(list_ptr lst, Generic x);
	void    (*walk) 	(list_ptr lst, int (*func)());
}; 

typedef list_ptr list;

/* DO NOT:
 * 	Do not call this function, please use macro "List()"
 * 	to create a link list.
 */
extern list list_constructor();

#define List(type) 		list_constructor(sizeof(type))


#endif 
