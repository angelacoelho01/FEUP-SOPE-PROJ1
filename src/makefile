CC = gcc
CFLAGS=-Wall
src_path := $(shell pwd)

all: xmod path

xmod: main.c
	$(CC) $(CFLAGS) main.c -o xmod

path:
#	@export PATH=$$PATH:$(src_path)
#	@echo $$PATH
	echo $(src_path)

clean:
	rm -f xmod
