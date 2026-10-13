CC      = g++
CFLAGS  = -g -Wall -std=c++11
TARGET  = P0
OBJS    = P0.o buildTree.o traversals.o

$(TARGET):	$(OBJS)
		$(CC) -o $(TARGET) $(OBJS)

P0.o:	P0.c buildTree.h traversals.h node.h
		$(CC) $(CFLAGS) -c P0.c

buildTree.o:	buildTree.c buildTree.h node.h
		$(CC) $(CFLAGS) -c buildTree.c

traversals.o:	traversals.c traversals.h node.h
		$(CC) $(CFLAGS) -c traversals.c

clean:
		/bin/rm -f *.o $(TARGET)

