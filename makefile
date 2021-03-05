CC=gcc
CFLAGS=-Wall
SRC_DIR=src
PERM_DIR=permissions
FSYS_DIR=filesystem

FILES = $(SRC_DIR)/main.c $(SRC_DIR)/$(PERM_DIR)/permissions.c $(SRC_DIR)/$(FSYS_DIR)/filesystem.c

make: ${FILES}
	$(CC) $(CFLAGS) -o xmod ${FILES}

clean:
	rm -f xmod
