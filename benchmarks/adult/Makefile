CC = gcc
CFLAGS = -Wall -O0

all: adult_float

adult_float: adult.o genann.o
	$(CC) $(CFLAGS) -DDATATYPE=1 -o $@ $^ $(LFLAGS)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY clean:
	-rm *.o
	-rm adult_*
