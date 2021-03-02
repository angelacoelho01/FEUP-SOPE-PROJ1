CC=gcc
CFLAGS=-Wall
SRC_DIR=src

FILES = $(SRC_DIR)/main.c

make: ${FILES}
	$(CC) $(CFLAGS) -o xmod ${FILES}

clean:
	rm -f xmod
