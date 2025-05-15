GCC = gcc
CFLAGS = -g -Wall -Wshadow

findc: findc.o project3.o
	$(GCC) $(CFLAGS) findc.o project3.o -o findc

findc.o: findc.c findc.h
	$(GCC) $(CFLAGS) -c findc.c findc.h

project3.o: project3.c
	$(GCC) $(CFLAGS) -c project3.c
