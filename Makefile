CC=gcc
CFLAGS=-std=c2x

OBJS= test.o

all: test

app: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o test

$(OBJS1) : %.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f test *.o
