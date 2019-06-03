/*
 * file name: exception.c
 * author   : Yu Liu
 * email    : <ilhanwnz@hotmail.com>
 * time     : Wed 29 May 2019 11:23:19 AM CST
 */

#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include "exception.h"

static char *ex_string[] = {
	"Initial capacity is full, please extend it.",	// capacity over flow
	"Nil vector, it possible do not initialize.",	// nil vector
	"Index over than length of vector.",
};

static char *strexception(enum eType etype)
{
	return ex_string[etype];
}
void exception_alloc()
{
	fprintf(stderr, "%s: %d allocate error", __FILE__, __LINE__);
	exit(ENOMEM);
}

void exception_vector(enum eType etype)
{
	fprintf(stderr, "vector exception: %s\n", strexception(etype));
	switch (etype) {
	case CAP_OFLOW:
		return;
	case NIL_VEC:
		assert(0);
	case ACC_OFLOW:
		return;
	}
}
