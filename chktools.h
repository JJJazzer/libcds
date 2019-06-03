/*
 * file name: chktools.h
 * author   : Yu Liu
 * email    : <ilhanwnz@hotmail.com>
 * time     : Wed 29 May 2019 11:18:02 AM CST
 */

#ifndef _CHKTOOLS_H
#define _CHKTOOLS_H

#include "stdlib.h"
#include "exception.h"

static inline void *chkmalloc(int size)
{
	void *x;
	x = malloc(size);
	if (x == NULL) 
		exception_alloc();	
	return x;
}
#endif
