example1: example1.o
	gcc -o example1 example1.o

example1.o: example1.c main_header.h
	gcc -O0 -g3 -Wall -c example1.c

getpid_ex: getpid_ex.o
	gcc -o getpid_ex getpid_ex.o

getpid_ex.o: getpid_ex.c main_header.h
	gcc -O0 -g3 -Wall -c getpid_ex.c

clean:
	@echo "This is a clean action"
	rm -rf example1 getpid_ex *.o

all: example1 getpid_ex