# DATATYPE:
# 0 : double
# 1 : float

CC = gcc
CFLAGS = -Wall -Wshadow -O0 -DDATATYPE=1
LFLAGS = -lm

all: iris	

debug: irisdebug

irisdebug: CFLAGS += -DDEBUG
irisdebug: iris

iris: iris.o genann.o
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY clean:
	-rm *.o
	-rm iris
