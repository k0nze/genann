CC = gcc
CFLAGS = -Wall -O0
LFLAGS = -lm

all: adult_double adult_float adult_fix16

adult_double: adult.o genann.o
	$(CC) $(CFLAGS) -DDATATYPE=0 -o $@ $^ $(LFLAGS)

adult_float: adult.o genann.o
	$(CC) $(CFLAGS) -DDATATYPE=1 -o $@ $^ $(LFLAGS)

adult_fix16: adult.fix16.data
	$(CC) -c $(CFLAGS) -Ilibfixmath libfixmath/fix16.c -o libfixmath/fix16.o
	$(CC) -c $(CFLAGS) -Ilibfixmath libfixmath/fix16_exp.c -o libfixmath/fix16_exp.o
	$(CC) -c $(CFLAGS) -DDATATYPE=2 -Ilibfixmath genann.c -o genann.o
	$(CC) -c $(CFLAGS) -DDATATYPE=2 -Ilibfixmath adult.c -o adult_fix16.o
	$(CC) $(CFLAGS) -DDATATYPE=2 -Ilibfixmath libfixmath/fix16.o libfixmath/fix16_exp.o genann.o adult_fix16.o -o adult_fix16 $(LFLAGS)

adult.fix16.data:
	../../float_to_fixed_csv adult.data adult.fix16.data

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY clean:
	-rm *.o
	-rm adult_*
