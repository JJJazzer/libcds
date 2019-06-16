/*
 * file name: include/bst.h
 * author   : Yu Liu
 * email    : <ilhanwnz@hotmail.com>
 * time     : Sat 15 Jun 2019 02:55:00 PM CST
 */

#ifndef _BST_H
#define _BST_H

#include "types.h"

#define T		Bst_T
typedef struct T 	*T;
typedef T		locate;

#define BST_INIT(type)	bst_constructor(sizeof(type))

extern T 	bst_constructor 	(int nbyte);
extern T 	bst_insert		(T bst, int x);
extern T 	bst_remove		(T bst, int x);
extern void 	bst_delete		(T *bst);
extern locate	bst_search		(T bst, int x);
extern locate 	bst_getmin		(T bst);
extern locate 	bst_getmax		(T bst);
extern int 	bst_retrieve		(locate bst);
extern void 	bst_inorder		(T bst, int (*CALLBACK)(void *x));
extern void 	bst_preorder		(T bst, int (*CALLBACK)(void *x));
extern void 	bst_postorder		(T bst, int (*CALLBACK)(void *x));

#undef T
#endif
