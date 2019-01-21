CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic

HEAD = masks.h state.h utils.h

.SUFFIXES: .c .o

.PHONY: all clean

emulate: emulate.o emulate_fde.o branch.o dataproc.o multiply.o singleDataTransfer.o utils.o
	$(CC) $(CFLAGS) -g $^ -o emulate

emulate.o : emulate.c emulate_fde.h $(HEAD)
	$(CC) $(CFLAGS) -c emulate.c

emulate_fde.o : emulate_fde.c emulate_fde.h $(HEAD)

branch.o : branch.c branch.h $(HEAD)
	$(CC) $(CFLAGS) -c branch.c

dataproc.o : dataproc.c dataproc.h $(HEAD)
	$(CC) $(CFLAGS) -c dataproc.c

multiply.o : multiply.c multiply.h $(HEAD)
	$(CC) $(CFLAGS) -c multiply.c

singleDataTransfer.o : singleDataTransfer.c singleDataTransfer.h $(HEAD)
	$(CC) $(CFLAGS) -c singleDataTransfer.c

utils.o : utils.c utils.h $(HEAD)
	$(CC) $(CFLAGS) -c utils.c

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
