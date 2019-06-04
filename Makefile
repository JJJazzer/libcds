#######################################################################
# file name: Makefile
# author   : Yu Liu
# email    : <ilhanwnz@hotmail.com>
# time     : Wed 29 May 2019 07:56:45 PM CST
#######################################################################

lib := libcds.a
obj := vector.o list.o stack.o exception.o 
src := vector.c list.c stack.c exception.c
CC  := gcc
CFLAGS += -DCOMPILER_GCC 
$(lib): $(obj)
	$(AR) $(ARFLAGS) $(lib) $(obj)
	ranlib $(lib)
$(obj): $(src)
clean:
	rm -rf *.o $(lib) 
