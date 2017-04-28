# DATATYPE:
# 0 : double
# 1 : float
# 2 : int32_t

CC = gcc
CFLAGS = -Wall -O0 -DDATATYPE=0
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
