CC      = g++
CFLAGS  = -g -Wall -std=c++11
TARGET  = P2
OBJS    = main.o scanner.o parser.o testTree.o testScanner.o

$(TARGET):	$(OBJS)
		$(CC) -o $(TARGET) $(OBJS)

main.o:	main.c scanner.h token.h parser.h node.h testTree.h testScanner.h
		$(CC) $(CFLAGS) -c main.c

Scanner.o:	scanner.c scanner.h token.h node.h
		$(CC) $(CFLAGS) -c scanner.c

parser.o:	parser.c parser.h token.h node.h
		$(CC) $(CFLAGS) -c parser.c

testTree.o:	testTree.c testTree.h
		$(CC) $(CFLAGS) -c testTree.c

testScanner.o:	testScanner.c testScanner.h
		$(CC) $(CFLAGS) -c testScanner.c

clean:
		/bin/rm -f *.o $(TARGET)

