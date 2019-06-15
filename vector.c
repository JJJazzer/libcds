#include "chktools.h"
#include "vector.h"
#include "exception_types.h"
#include "exception.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define vec_is_nil(v) 	\
{			\
	if (v == NULL)  \
		exception_vector(NIL_PTR); \
}

#define T	Vector_T
struct T {
	Generic elem;
	struct vector_info *vi;
};
struct vector_info {
	int len;
	int cap;
	int nbyte;
};

_Bool 	vec_empty	(T v);
void 	vec_pushback	(T v, Generic elem);
void	vec_pushfront	(T v, Generic elem);
Generic	vec_get_elem_by_idx(T v, int index);
int 	vec_size	(T v);
int 	vec_capacity	(T v);
Generic vec_pop_back	(T v);
Generic vec_pop_front	(T v);
void 	vec_insert	(T v, Generic elem, int index);
Generic vec_remove_by_idx(T v, int index);
void	vec_delete	(T *v);
int 	vec_find_elem	(T v, Generic elem);
void 	vec_walk	(T v, int (*func)());

static inline int streq(const char *str1, const char *str2)
{
	return strcmp(str1, str2) ? 0 : 1;
}

static inline Generic reallocate(Generic oldelem, int nbyte, int length)
{
	Generic newelem = realloc(oldelem, 2 * length);
	memset(newelem, 0, length);
	memcpy(newelem, oldelem, nbyte * length);
	return newelem;
}

static inline Generic double_allocate(Generic oldelem, int nbyte, int old_length)
{
	return reallocate(oldelem, nbyte, 2 * old_length);
}

T vector_constructor(int cap, int nbyte)
{
	T v;
	v = chkmalloc(sizeof(*v));
	v->vi = chkmalloc(sizeof(*(v->vi)));
	v->vi->cap = cap;
	v->elem = chkmalloc(cap * nbyte);
	memset(v->elem, 0, cap * nbyte);
	v->vi->len = 0;
	v->vi->nbyte = nbyte;
	return v;
}

_Bool vec_empty(T v)
{
	vec_is_nil(v && v->vi && v->elem);
	assert(v);
	return v->vi->len == 0;
}

int vec_size(T v)
{
	vec_is_nil(v && v->vi && v->elem);
	assert(v);
	return v->vi->len;
}
int vec_capacity(T v)
{
	vec_is_nil(v && v->vi && v->elem);
	assert(v);
	return v->vi->cap;
}
void vec_push_back(T v, Generic elem)
{
	int len = v->vi->len;
	if (len >= v->vi->cap) { 
		/* Extend memory */
		v->elem = double_allocate(v->elem, v->vi->nbyte, v->vi->cap);
		v->vi->cap *= 2; 
	}
	memcpy(v->elem + (len * v->vi->nbyte), elem, v->vi->nbyte);
	v->vi->len++;
}

Generic vec_pop_back(T v)
{
	vec_is_nil(v && v->vi && v->elem);
	assert(v);
	v->vi->len--;
	return (v->elem + (v->vi->len * v->vi->nbyte));
}

void vec_insert(T v, Generic elem, int index)
{
	vec_is_nil(v && v->vi && v->elem);
	assert(v);
	if (index > v->vi->len) {
		// throw exception
		exception_vector(ACC_OFLOW);

	} else {
		if (v->vi->len >= v->vi->cap) {
			v->elem = double_allocate(v->elem, v->vi->nbyte, v->vi->cap);
			v->vi->cap *= 2;
		} else if (index == v->vi->len) {
			vec_push_back(v, elem);
			return;
		}
		memcpy(v->elem + ((index + 1) * v->vi->nbyte), v->elem + index * v->vi->nbyte, v->vi->nbyte * (v->vi->len - index));
		memcpy(v->elem + (index * v->vi->nbyte), elem, v->vi->nbyte);
		v->vi->len++;
	}
}

void vec_delete(T *v)
{
	free((*v)->elem);
	free(*v);
}

Generic vec_get_elem_by_idx(T v, int index)
{
	char *warn_info = "warning: index should be > 0\n";
	vec_is_nil(v && v->vi && v->elem);
	assert(v);
	if (index >= v->vi->cap) 
		exception_vector(CAP_OFLOW);
	if (index < 0) {
		index = -index;
		fprintf(stderr, "%s", warn_info);
	} 
	return (v->elem + (index * v->vi->nbyte));
}

int vec_find_elem(T v, Generic elem)
{
	__WALK_VECTOR(0, v->vi->len, 1,
		if (memcmp(elem, v->elem + (i * v->vi->nbyte),
				v->vi->nbyte) == 0)
			return i);
	/* Not found */
	return -1;
}

void vec_push_front(T v, Generic elem)
{
	return vec_insert(v, elem, 0);
}

Generic vec_pop_front(T v)
{
	return vec_remove_by_idx(v, 0);
}

Generic vec_remove_by_idx(T v, int index)
{
	vec_is_nil(v && v->vi && v->elem);
	if (index >= v->vi->len) {
		exception_vector(ACC_OFLOW);
		return NULL;
	}

	Generic x = v->elem + (index * v->vi->nbyte);
	memcpy(v->elem + (index * v->vi->nbyte),
			v->elem + ((index + 1) * v->vi->nbyte),
			v->vi->nbyte * (v->vi->len - index));
	v->vi->len--;
	return x;
}

void vec_walk(T v, int (*func) ())
{
	vec_is_nil(v && v->vi && v->elem);
	__WALK_VECTOR(0, v->vi->len, 1, func(v->elem + (i * v->vi->nbyte)));
}

