CC = gcc
CFLAGS = -Wall -O2
LFLAGS = -lm

all: iris_double iris_float iris_fix16

iris_double: iris.o genann.o
	$(CC) $(CFLAGS) -DDATATYPE=0 -o $@ $^ $(LFLAGS)

iris_float: iris.o genann.o
	$(CC) $(CFLAGS) -DDATATYPE=1 -o $@ $^ $(LFLAGS)

iris_fix16: bezdekIris.fix16.data
	$(CC) -c $(CFLAGS) -Ilibfixmath libfixmath/fix16.c -o libfixmath/fix16.o
	$(CC) -c $(CFLAGS) -Ilibfixmath libfixmath/fix16_exp.c -o libfixmath/fix16_exp.o
	$(CC) -c $(CFLAGS) -DDATATYPE=2 -Ilibfixmath genann.c -o genann.o
	$(CC) -c $(CFLAGS) -DDATATYPE=2 -Ilibfixmath iris.c -o iris_fix16.o
	$(CC) $(CFLAGS) -DDATATYPE=2 -Ilibfixmath libfixmath/fix16.o libfixmath/fix16_exp.o genann.o iris_fix16.o -o iris_fix16 $(LFLAGS)

bezdekIris.fix16.data:
	../../float_to_fixed_csv bezdekIris.data bezdekIris.fix16.data

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY clean:
	-rm *.o
	-rm iris_*
