CC=gcc
CFLAGS=-Wall
shell: shell.c
	$(CC) $(CFLAGS) -o $@ shell.c
clean:
	rm -f shell
