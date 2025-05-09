CC      = g++
CFLAGS  = -g -Wall -std=c++11
TARGET  = P4
OBJS    = main.o scanner.o parser.o semantics.o

$(TARGET):	$(OBJS)
		$(CC) -o $(TARGET) $(OBJS)

main.o:	main.c scanner.h token.h parser.h node.h semantics.h
		$(CC) $(CFLAGS) -c main.c

Scanner.o:	scanner.c scanner.h token.h node.h
		$(CC) $(CFLAGS) -c scanner.c

parser.o:	parser.c parser.h token.h node.h
		$(CC) $(CFLAGS) -c parser.c

semantics.o:	semantics.c semantics.h
		$(CC) $(CFLAGS) -c semantics.c

clean:
		/bin/rm -f *.o $(TARGET)

