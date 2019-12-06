# Makefile for Generic Set ADT

CC = gcc
CFLAGS = -Wall -Werror -g

all : testSetG

testSetG : testSetG.o SetG.o  positiveIntSet.o stringSet.o 
	$(CC) -o ts testSetG.o SetG.o positiveIntSet.o stringSet.o 

testSetG.o : testSetG.c SetG.h positiveIntSet.h stringSet.h
	$(CC) $(CFLAGS) -c testSetG.c

SetG.o : SetG.c SetG.h  
	$(CC) $(CFLAGS) -c SetG.c

positiveIntSet.o : positiveIntSet.c positiveIntSet.h 
	$(CC) $(CFLAGS) -c positiveIntSet.c

stringSet.o : stringSet.c stringSet.h  
	$(CC) $(CFLAGS) -c stringSet.c


clean :
	rm -f *.o ts core

