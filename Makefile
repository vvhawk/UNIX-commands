TARGET = tree
CC     = gcc
CFLAGS = -g -Wall -Wvla -fsanitize=address

ls: ls.c
	$(CC) $(CFLAGS) -o $@ $^

find: find.c
	$(CC) $(CFLAGS) -o $@ $^

tree: tree.c
	$(CC) $(CFLAGS) -o $@ $^

all: ls find tree

clean:
	rm -rf ls *.o *.a *.dylib *.dSYM
	rm -rf find *.o *.a *.dylib *.dSYM
	rm -rf tree *.o *.a *.dylib *.dSYM
