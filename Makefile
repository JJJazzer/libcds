#######################################################################
# file name: Makefile
# author   : Yu Liu
# email    : <ilhanwnz@hotmail.com>
# time     : Wed 29 May 2019 07:56:45 PM CST
#######################################################################

lib := libcds.a
obj := vector.o list.o stack.o bst.o exception.o 
src := vector.c list.c stack.c bst.c exception.c
CC  := gcc
VPATH := include
CFLAGS += -Iinclude -DCOMPILER_GCC 
$(lib): $(obj)
	$(AR) $(ARFLAGS) $(lib) $(obj)
	ranlib $(lib)
$(obj): $(src)
test: $(lib)
	$(CC) main.c -L. -lcds
clean:
	rm -rf *.o $(lib) a.out
