open_example: open_example.o
	gcc -o open_example open_example.o

open_example.o: open_example.c main_header.h
	gcc -O0 -g3 -Wall -c open_example.c

clean:
	@echo "This is a clean action"
	rm -rf open_example *.o

all: open_example