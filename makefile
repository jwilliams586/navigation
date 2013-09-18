CC=gcc

run: main.o
	$(CC) -o run main.o

clean:
	rm run *.o

.SUFFIXES: .o .c

.c.o :
	$(CC) -c $<

