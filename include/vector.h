/*
 * file name: libcds.h
 * author   : Yu Liu
 * email    : <ilhanwnz@hotmail.com>
 * time     : Wed 29 May 2019 10:39:47 AM CST
 */

#ifndef _VECTOR_H
#define _VECTOR_H

#include "types.h"

#define T	Vector_T
typedef struct T *T;

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

typedef int (*CALLBACK)(void *x);

/* It used to consturct an object of vector. */
#define VECTOR_INIT(type, cap) 	vector_constructor(cap, sizeof(type))

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
extern T 	vector_constructor	(int cap, int nbyte);
extern _Bool 	vec_empty 		(T vec);
extern int 	vec_size 		(T vec);
extern int 	vec_capacity 		(T vec);
extern void 	vec_pushback		(T vec, Generic elem);
extern Generic 	vec_popback 		(T vec);
extern void 	vec_pushfront 		(T vec, Generic elem);
extern Generic 	vec_popfront 		(T vec);
extern void 	vec_insert		(T vec, Generic elem, int index);
extern Generic 	vec_remove_by_idx	(T vec, int index);
extern void 	vec_delete		(T *vec);
extern Generic 	vec_get_elem_by_idx 	(T vec, int index);
extern int 	vec_find_elem 		(T vec, Generic elem);
extern void 	vec_walk		(T vec, CALLBACK p);

#undef T
#endif
