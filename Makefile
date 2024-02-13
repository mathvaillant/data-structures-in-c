CC=gcc

all: SinglyLinkedLists.c
	$(CC) -o SinglyLinkedLists SinglyLinkedLists.c

clean: 
	rm -f SinglyLinkedLists
