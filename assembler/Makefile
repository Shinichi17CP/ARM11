CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

HEAD = codes.h state.h utils.h tables.h

.SUFFIXES: .c .o

.PHONY: all clean

assemble: assemble.o branch.o dataProc.o multiply.o sdt.o special.o utils.o
	$(CC) $(CFLAGS) -g $^ -o assemble

assemble.o: assemble.c $(HEAD)
	$(CC) $(CFLAGS) -c assemble.c

branch.o : branch.c branch.h $(HEAD)
	$(CC) $(CFLAGS) -c branch.c

dataProc.o : dataProc.c dataProc.h $(HEAD)
	$(CC) $(CFLAGS) -c dataProc.c

multiply.o : multiply.c multiply.h $(HEAD)
	$(CC) $(CFLAGS) -c multiply.c

sdt.o : sdt.c sdt.h $(HEAD)
	$(CC) $(CFLAGS) -c sdt.c

special.o : special.c special.h $(HEAD)
	$(CC) $(CFLAGS) -c special.c

utils.o : utils.c utils.h $(HEAD)
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
