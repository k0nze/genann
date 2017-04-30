# DATATYPE
# 0 : double
# 1 : float

CCFLAGS = -Wall -Wshadow -O2 -g -DDATATYPE=1
LFLAGS = -lm


all: test example1 example2 example3 example4

test: test.o genann.o
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)
	./$@

example1: example1.o genann.o
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

example2: example2.o genann.o
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

example3: example3.o genann.o
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

example4: example4.o genann.o
	$(CC) $(CCFLAGS) -o $@ $^ $(LFLAGS)

.c.o:
	$(CC) -c $(CCFLAGS) $< -o $@


.PHONY clean:
	-rm *.o
	-rm *.exe
	-rm persist.txt
	-rm example1
	-rm example2
	-rm example3
	-rm example4
	-rm test
	-rm float_to_fixed_csv
