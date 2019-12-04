# SortLab Makefile

CC = gcc
CFLAGS = -Wall -Werror -g -pg
LDFLAGS=

sorter: sorter.o
	$(CC) -o sorter $(CFLAGS) sorter.o

clean:
	rm -f sorter sorter.o
