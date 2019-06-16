/*
 * file name: bst.c
 * author   : Yu Liu
 * email    : <ilhanwnz@hotmail.com>
 * time     : Sat 15 Jun 2019 11:05:38 PM CST
 */

#include "bst.h"
#include "chktools.h"
#include "exception.h"
#include <assert.h>

#define T	Bst_T

struct T {
	int 	 x;		/* Replace void* to int,
				 * Because i don't found a solution,
				 * to deal void*
				 */
	T	left, right;
};

T bst_constructor(int nbyte)
{
	T t;
	t = NULL;
	return t;
}

T bst_insert(T bst, int x)
{
	if (!bst) {
		bst = chkmalloc(sizeof(*bst));
		if (bst == NULL) {
			exception_alloc();
		} else {
			bst->x = x;
			bst->left = bst->right = NULL;
		}
	} else if (x < bst->x) {
		bst->left = bst_insert(bst->left, x);
	} else if (x > bst->x) {
		bst->right = bst_insert(bst->right, x);
	}
	return bst;
}

locate bst_search(T bst, int x)
{
	if (bst == NULL)
		return NULL;
	if (x < bst->x)
		return bst_search(bst->left, x);
	else if (x > bst->x)
		return bst_search(bst->right, x);
	else
		return bst;
}

locate bst_getmin(T bst)
{
	if (bst == NULL)
		return NULL;	
	if (bst->left == NULL)
		return bst;
	else 
		return bst_getmin(bst->left);
}

locate bst_getmax(T bst)
{
	if (bst == NULL)
		return NULL;
	if (bst->right == NULL)
		return bst;
	else
		return bst_getmax(bst->right);
}

int bst_retrieve(T bst)
{
	return bst->x;
}

T bst_remove(T bst, int x)
{
	T tmp_node;
	if (T == NULL)
		return NULL;
	else if (x < bst->x)
		bst->left = bst_remove(bst->left, x);
	else if (x > bst->x)
		bst->right = bst_remove(bst->right, x);
	else {
		if (bst->left && bst->right) {
			tmp_node = bst_getmin(bst->right);
			bst->x = tmp_node->elem;
			bst->right = bst_remove(bst->right, bst->x);

		} else {
			tmp_node = bst;
			if (bst->left == NULL)
				bst = bst->right;
			else if (bst->right == NULL)
				bst = bst->left;
			free(tmp_node);
		}
	}
	return bst;

void bst_inorder(T bst, int (*CALLBACK)(void*))
{
	if (bst != NULL) {
		bst_inorder(bst->left, CALLBACK);
		CALLBACK(&bst->x);
		bst_inorder(bst->right, CALLBACK);
	}
}
