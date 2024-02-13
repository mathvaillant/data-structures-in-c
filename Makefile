CC=gcc
FILE=<name of the C file>

all: $(FILE).c
	$(CC) -o $(FILE) $(FILE).c

clean: 
	rm -f $(FILE)
