# The C function library of data structure  (unfinish)
## Introduction
"libcds" is a C function library, like *glibc*. It is object-oriented implemented with function pointer, so have some trouble. 
Such as, it must passing arguments of itself object.

```
  vector v1 = Vector();
  v1->push_back(v1, elements);
```
Therefore, "libcds" isn't traditional object-oriented, like C++/Java, Generally, it is offer convience to write compiler and other system softwares for me.

## How to compile it?
Typing command `make` to compiled. It used "gcc" extend functional by default,if setting flags "COMPILER_GCC".
Using *POSIX Standard* if change flags "CC" to another compiler and closing "COMPILER_GCC" flags.

## How to use it?
### *Structure of vector*
Vector structure is a linear list. Plese setting type and capacity, if you want to use it. Usage:
```
vector v1 = Vector(type, capacity);
v1->size(v1);
```
Vector structure have 13 member functions:
* bool empty(object)
* int size(object)
* int capacity(object)
* void push_back(object, elements)
* elements pop_back(object)
* void push_front(object, elements)
* elements pop_front(object)
* void insert(object, elements, index)
* elements remove_by_index(object, index)
* void delete(object)
* elements get_elem_by_index(object, index)
* int find_elem(object, elements)
* void walk(object, callback function)

Example:
```
int print(void *x)
{
  printf("%d\n", *_TAKE_OFF_VOIDPTR(int, x));
}
int main(void) 
{
  vector v1 = Vector(int, 5);
  int i;
  for (i = 0; i < 5; i++)
    v1->push_back(v1, &i);
  v1->walk(v1, print);
}

```
