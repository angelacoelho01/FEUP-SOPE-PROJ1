CC=gcc
CFLAGS=-Wall

SRC_DIR=src
PERM_DIR=permissions

FILES = $(SRC_DIR)/main.c $(SRC_DIR)/$(PERM_DIR)/xmod.c

make: ${FILES}
	$(CC) $(CFLAGS) -o xmod ${FILES}

clean:
	rm -f xmod

