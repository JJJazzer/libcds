/*
 * file name: list.h
 * author   : Yu Liu
 * email    : <ilhanwnz@hotmail.com>
 * time     : Fri 31 May 2019 06:34:52 PM CST
 */

#ifndef _LIST_H
#define _LIST_H

typedef struct list *list_ptr;
typedef struct list_info *list_info;

struct list {
	struct elem *head;
	list_info l_info;
	_Bool (*empty) 		(list_ptr lst);
	int   (*size) 		(list_ptr lst);
	void  (*push_back)	(list_ptr lst, void *x);
	void* (*pop_back) 	(list_ptr lst);
	void  (*insert)		(list_ptr lst, void *x, int index);
	void* (*remove_by_index)(list_ptr lst, int index); 
	void  (*walk) 		(list_ptr lst, int (*func)());
}; 

typedef list_ptr list;

/* DO NOT:
 * 	Do not call this function, please use macro "List()"
 * 	to create a link list.
 */
extern list list_constructor();

#define List 		list_constructor


#endif 
