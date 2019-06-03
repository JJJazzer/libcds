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

struct vector_info {
	int len;
	int cap;
	int nbyte;
};
_Bool vec_empty(vector_ptr v);
void vec_push_back(vector_ptr v, Generic elem);
void vec_push_front(vector_ptr v, Generic elem);
Generic get_elem_by_index(vector_ptr v, int index);
int vec_size(vector_ptr v);
int vec_capacity(vector_ptr v);
Generic vec_pop_back(vector_ptr v);
Generic vec_pop_front(vector_ptr v);
void insert(vector_ptr v, Generic elem, int index);
Generic remove_by_index(vector_ptr v, int index);
void vec_delete(vector_ptr *v);
int vec_find_elem(vector_ptr v, Generic elem);
void vec_walk(vector_ptr v, int (*func)());

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

vector_ptr vector_constructor(int cap, int nbyte)
{
	vector_ptr v;
	v = chkmalloc(sizeof(*v));
	v->vi = chkmalloc(sizeof(*(v->vi)));
	v->vi->cap = cap;
	v->elem = chkmalloc(cap * nbyte);
	memset(v->elem, 0, cap * nbyte);
	v->vi->len = 0;
	v->vi->nbyte = nbyte;

	/* Function initial */
	v->empty = vec_empty;
	v->push_back = vec_push_back;
	v->push_front = vec_push_front;
	v->pop_front = vec_pop_front;
	v->get_elem_by_index = get_elem_by_index;
	v->size = vec_size;
	v->capacity = vec_capacity;
	v->pop_back = vec_pop_back;
	v->insert   = insert;
	v->delete   = vec_delete;
	v->find_elem = vec_find_elem;
	v->remove_by_index = remove_by_index;
	v->walk = vec_walk;
	return v;
}

_Bool vec_empty(vector_ptr v)
{
	vec_is_nil(v && v->vi && v->elem);
	assert(v);
	return v->vi->len == 0;
}

int vec_size(vector_ptr v)
{
	vec_is_nil(v && v->vi && v->elem);
	assert(v);
	return v->vi->len;
}
int vec_capacity(vector_ptr v)
{
	vec_is_nil(v && v->vi && v->elem);
	assert(v);
	return v->vi->cap;
}
void vec_push_back(vector_ptr v, Generic elem)
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

Generic vec_pop_back(vector_ptr v)
{
	vec_is_nil(v && v->vi && v->elem);
	assert(v);
	v->vi->len--;
	return (v->elem + (v->vi->len * v->vi->nbyte));
}

void insert(vector_ptr v, Generic elem, int index)
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
			v->push_back(v, elem);
			return;
		}
		memcpy(v->elem + ((index + 1) * v->vi->nbyte), v->elem + index * v->vi->nbyte, v->vi->nbyte * (v->vi->len - index));
		memcpy(v->elem + (index * v->vi->nbyte), elem, v->vi->nbyte);
		v->vi->len++;
	}
}

void vec_delete(vector_ptr *v)
{
	free((*v)->elem);
	free(*v);
}

Generic get_elem_by_index(vector_ptr v, int index)
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

int vec_find_elem(vector_ptr v, Generic elem)
{
	__WALK_VECTOR(0, v->vi->len, 1,
		if (memcmp(elem, v->elem + (i * v->vi->nbyte),
				v->vi->nbyte) == 0)
			return i);
	/* Not found */
	return -1;
}

void vec_push_front(vector_ptr v, Generic elem)
{
	return v->insert(v, elem, 0);
}

Generic vec_pop_front(vector_ptr v)
{
	return remove_by_index(v, 0);
}

Generic remove_by_index(vector_ptr v, int index)
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

void vec_walk(vector_ptr v, int (*func) ())
{
	vec_is_nil(v && v->vi && v->elem);
	__WALK_VECTOR(0, v->vi->len, 1, func(v->elem + (i * v->vi->nbyte)));
}

