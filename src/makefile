CC = gcc
CFLAGS=-Wall
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
mkfile_dir := $(dir $(mkfile_path))
PATH := $(PATH):$(mkfile_path)

all: xmod path

xmod: main.c
	$(CC) $(CFLAGS) main.c -o xmod

path:
	@echo $(PATH)

clean:
	rm -f xmod
