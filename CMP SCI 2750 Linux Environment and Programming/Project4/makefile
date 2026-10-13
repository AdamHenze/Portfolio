GCC = gcc
CFLAGS = -g -Wall -Wshadow

mathwait: help.o project4.o
	$(GCC) $(CFLAGS) help.o project4.o -o mathwait

help.o: help.c help.h
	$(GCC) $(CFLAGS) -c help.c help.h

project4.o: project4.c
	$(GCC) $(CFLAGS) -c project4.c
