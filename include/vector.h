/*
 * file name: libcds.h
 * author   : Yu Liu
 * email    : <ilhanwnz@hotmail.com>
 * time     : Wed 29 May 2019 10:39:47 AM CST
 */

#ifndef _VECTOR_H
#define _VECTOR_H

#include "types.h"

typedef struct vector *vector_ptr;
typedef struct vector_info *vector_info;

/*
 *****************************************************************
 * Member function:				     	 	 *
 * 						     		 *
 * empty:     	Check of the vector whether empty.    		 *
 * size :     	Return of the vector size.	    		 *
 * capacity:  	Return of the vector capacity. 	    		 *
 * push_back: 	Push an element into vector's tail.  		 *
 * pop_back:  	Pop an element from vector's tail.	   	 *
 * push_front:  Push an element into vector's head.		 *
 * pop_front:   Pop an element from vector's head. 	         *
 * insert:    	Insert an element into vector by index.		 *
 * remove_by_index: Remove an element by index.			 *
 * delete: 	Delete vector.					 *
 * get_elem_by_index: get an element from vector by index.	 *
 * find_elem:   Find an element in vector.			 *
 * walk: 	Walking to vector.				 *
 *****************************************************************
 */
struct vector {
	Generic  elem;
	vector_info vi;
	_Bool   (*empty)     (vector_ptr v);
	int     (*size)      (vector_ptr v);
	int     (*capacity)  (vector_ptr v);
	void    (*push_back) (vector_ptr v, Generic elem);
	Generic (*pop_back)  (vector_ptr v);
	void    (*push_front)(vector_ptr v, Generic elem);
	Generic (*pop_front) (vector_ptr v);
	void    (*insert)    (vector_ptr v, Generic elem, int index);
	Generic (*remove_by_index)    (vector_ptr v, int index);
	void    (*delete)    (vector_ptr *v);
	Generic (*get_elem_by_index) (vector_ptr v, int index);
	int     (*find_elem) (vector_ptr v, Generic elem);
	void    (*walk)      (vector_ptr v, int (*func) ());
};

typedef vector_ptr vector;

/* It used to consturct an object of vector. */
#define Vector(type, cap) 	vector_constructor(cap, sizeof(type))

#define __WALK_VECTOR(start, end, step, func) \
{					\
	int i;				\
	for (i = start; i < end; i += step) { \
		func; 			\
	}				\
}					\

/* DO NOT: 
 * 	Don't call this function, you should call macro of "Vector(type, cap)",
 * 	This function should call never.
 */
extern vector_ptr vector_constructor(int cap, int nbyte);

#endif
