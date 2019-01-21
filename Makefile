CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

.SUFFIXES: .c .o

.PHONY: all clean

all: assemble emulate

assemble:
	cd assembler && make assemble

emulate:
	cd emulator && make emulate

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
