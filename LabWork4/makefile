example1: example1.o
	gcc -o example1 example1.o

example1.o: example1.c main_header.h
	gcc -O0 -g3 -Wall -c example1.c

number1: number1.o
	gcc -o number1 number1.o

number1.o: number1.c main_header.h
	gcc -O0 -g3 -Wall -c number1.c

number2: number2.o
	gcc -o number2 number2.o

number2.o: number2.c main_header.h
	gcc -O0 -g3 -Wall -c number2.c

env_var: env_var.o
	gcc -o env_var env_var.o

env_var.o: env_var.c main_header.h
	gcc -O0 -g3 -Wall -c env_var.c

env_calls: env_calls.o
	gcc -o env_calls env_calls.o

env_calls.o: env_calls.c main_header.h
	gcc -O0 -g3 -Wall -c env_calls.c

clean:
	@echo "This is a clean action"
	rm -rf example1 number1 number2 env_var env_calls *.o

all: example1 number1 number2 env_var env_calls