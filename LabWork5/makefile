fork_example: fork_example.o
	gcc -o fork_example fork_example.o

fork_example.o: fork_example.c main_header.h
	gcc -O0 -g3 -Wall -c fork_example.c

clean:
	@echo "This is a clean action"
	rm -rf fork_example *.o

all: fork_example