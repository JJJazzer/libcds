/*
 * file name: libcds.h
 * author   : Yu Liu
 * email    : <ilhanwnz@hotmail.com>
 * time     : Wed 29 May 2019 10:39:47 AM CST
 */

#ifndef _LIBCDS_H
#define _LIBCDS_H

typedef void *generic; 

#include "vector.h"

#line 15 "libcs.h"

/* Take off the "clothing" of void pointer.  */
#define _TAKE_OFF_VOIDPTR(type, vptr) \
	(type*) (vptr)

#include "list.h"

#line 23 "libcds.h"


#endif
