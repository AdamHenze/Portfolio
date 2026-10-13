CC      = g++
CFLAGS  = -g -Wall -std=c++11
TARGET  = P1
OBJS    = main.o scanner.o testScanner.o

$(TARGET):	$(OBJS)
		$(CC) -o $(TARGET) $(OBJS)

main.o:	main.c scanner.h testScanner.h token.h
		$(CC) $(CFLAGS) -c main.c

Scanner.o:	scanner.c scanner.h token.h
		$(CC) $(CFLAGS) -c scanner.c

testScanner.o:	testScanner.c testScanner.h token.h
		$(CC) $(CFLAGS) -c testScanner.c

clean:
		/bin/rm -f *.o $(TARGET)

