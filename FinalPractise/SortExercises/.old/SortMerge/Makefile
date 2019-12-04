CC=gcc
CFLAGS=-Wall -Werror
CFLAGS+=-g
#CFLAGS+=-pg

msort : msort.o
	$(CC) -o msort msort.o

clean :
	rm -f msort msort.o gmon.out core
