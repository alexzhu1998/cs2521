# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -Werror -c

all: treeLab clean

treeLab : treeLab.o BSTree.o
	$(CC) -o treeLab treeLab.o BSTree.o

treeLab.o : treeLab.c BSTree.h
	$(CC) $(CFLAGS) treeLab.c

BSTree.o : BSTree.c BSTree.h
	$(CC) $(CFLAGS) BSTree.c

clean :
	rm -rf *.o
