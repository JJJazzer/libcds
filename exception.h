/*
 * file name: exception.h
 * author   : Yu Liu
 * email    : <ilhanwnz@hotmail.com>
 * time     : Wed 29 May 2019 07:51:53 PM CST
 */

#ifndef _EXCEPTION_H
#define _EXCEPTION_H

#include "exception_types.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef COMPILER_GCC
extern _Noreturn void exception_alloc();
#else
extern void exception_alloc() __attribute__((noreturn));
#endif

extern void exception_vector(enum eType etype);
extern void exception_list(enum eType etype);

#endif 
