CC=gcc
CFLAGS=-Wall

SRC_DIR=src
PERM_DIR=permissions
FSYS_DIR=filesystem
INC_DIR=inputcheck
SIG_DIR=signals

FILES = $(SRC_DIR)/main.c $(SRC_DIR)/$(PERM_DIR)/xmod.c $(SRC_DIR)/$(FSYS_DIR)/filesystem.c $(SRC_DIR)/utils.c $(SRC_DIR)/$(INC_DIR)/inputcheck.c $(SRC_DIR)/$(SIG_DIR)/signals.c

make: ${FILES}
	$(CC) $(CFLAGS) -o xmod ${FILES}

clean:
	rm -f xmod

