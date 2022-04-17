fork_example: fork_example.o
	gcc -o fork_example fork_example.o

fork_example.o: fork_example.c main_header.h
	gcc -O0 -g3 -Wall -c fork_example.c

at_on_exit: at_on_exit.o
	gcc -o at_on_exit at_on_exit.o

at_on_exit.o: at_on_exit.c main_header.h
	gcc -O0 -g3 -Wall -c at_on_exit.c

number1: number1.o
	gcc -o number1 number1.o

number1.o: number1.c main_header.h
	gcc -O0 -g3 -Wall -c number1.c

clean:
	@echo "This is a clean action"
	rm -rf fork_example at_on_exit number1 *.o

all: fork_example at_on_exit number1