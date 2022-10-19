CC=gcc
CFLAGS=-O2

minheap: minheap.c
	$(CC) $(CFLAGS) -o minheap minheap.c
