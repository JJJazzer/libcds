# The C function library of data structure  (unfinish)
## Introduction
"libcds" is a C function library, like *glibc*. It is object-oriented implemented with function pointer, so have some trouble. 
Such as, it must passing arguments of itself object.

```
  vector v1 = Vector();
  vec_push_back(v1, elements);
```
Therefore, "libcds" isn't traditional object-oriented, like C++/Java, Generally, it is offer convience to write compiler and other system softwares for me.

## How to compile it?
Typing command `make` to compiled. It used "gcc" extend functional by default,if setting flags "COMPILER_GCC".
Using *POSIX Standard* if change flags "CC" to another compiler and closing "COMPILER_GCC" flags.

## How to use it?
You only need include a header file "libcds.h", and add options "-L(directory with "libcds.h") -lcds" at compile-time.
### *Structure of vector*
Vector structure is a linear list that implementation with array. Please setting type and capacity, if you want to use it. Usage:
```
vector v1 = Vector(type, capacity);
vec_size(v1);
```
Vector structure have 13 member functions:
* ***bool empty(object)***
* ***int size(object)***
* ***int capacity(object)***
* ***void pushback(object, elements)***
* ***elements popback(object)***
* ***void pushfront(object, elements)***
* ***elements popfront(object)***
* ***void insert(object, elements, index)***
* ***elements remove_by_index(object, index)***
* ***void delete(object)***
* ***elements get_elem_by_idx(object, index)***
* ***int find_elem(object, elements)***
* ***void walk(object, callback function)***

Example:
```
int print(void *x)
{
  printf("%d\n", *_TAKE_OFF_VOIDPTR(int, x));
}
int main(void) 
{
  Vector_T v1 = VECTOR_INIT(int, 5);
  int i;
  for (i = 0; i < 5; i++)
    vec_push_back(v1, &i);
  vec_walk(v1, print);
}

```
### *Structure of list*
List structure is a linear list that implementation with link list. It just need an arguments of type.
Usage:
```
List_T lst1 = LIST_INIT(string)
```
List structure have 9 member functions:
* ***bool empty(object)***
* ***int size(object)***
* ***void pushback(object, elements)***
* ***elements popback(object)***
* ***void insert(object, elements, index)***
* ***elements remove_by_idxx(object, index)***
* ***void delete(object)***
* ***int find_elem(object, elements)***
* ***void walk(object, callback function)***

Example:
```
List_T lst = LIST_INIT(string)
list_pushback(lst, "first elements");
list_walk(lst, printlst);
```

### *Structure of stack*
This stack structure is implementation with link list. 
Usage:
```
Stack_T stk1 = STACK_INIT(string)
```
This structure just have 5 member functions:
* ***bool empty(object)***
* ***int size(object)***
* ***void push(object, elements)***
* ***elements pop(object)***
* ***void delete(object)***

Example:
```
Stack_T stk1 = STACK_INIT(string)
stack_push(stk1, "first elements");
string s = stack_pop(stk1);
```
