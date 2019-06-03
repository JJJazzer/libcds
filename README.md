# The C function library of data structure  (unfinish)
## Introduction
`libcds` is a C function library, like glibc. It is object-oriented implemented with function pointer, so have some trouble. 
Such as, it must passing arguments of itself object.

```
  vector v1 = Vector();
  v1->push_back(v1, elements);
```
Therefore, "libcds" isn't traditional object-oriented, like C++/Java, Generally, it is offer convience to write compiler and other system softwares for me.

## How to compile it?
