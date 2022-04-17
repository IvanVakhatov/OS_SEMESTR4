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

number2: number2.o
	gcc -o number2 number2.o

number2.o: number2.c main_header.h
	gcc -O0 -g3 -Wall -c number2.c

number3: number3.o
	gcc -o number3 number3.o

number3.o: number3.c main_header.h
	gcc -O0 -g3 -Wall -c number3.c

number4: number4.o
	gcc -o number4 number4.o

number4.o: number4.c main_header.h
	gcc -O0 -g3 -Wall -c number4.c

number5: number5.o
	gcc -o number5 number5.o

number5.o: number5.c main_header.h
	gcc -O0 -g3 -Wall -c number5.c

number6: number6.o
	gcc -o number6 number6.o

number6.o: number6.c main_header.h
	gcc -O0 -g3 -Wall -c number6.c

number7: number7.o
	gcc -o number7 number7.o

number7.o: number7.c main_header.h
	gcc -O0 -g3 -Wall -c number7.c

env_vars: env_vars.o
	gcc -o env_vars env_vars.o

env_vars.o: env_vars.c main_header.h
	gcc -O0 -g3 -Wall -c env_vars.c

clean:
	@echo "This is a clean action"
	rm -rf fork_example at_on_exit number1 number2 number3 number4 number5 number6 number7 env_vars *.o
	
all: fork_example at_on_exit number1 number2 number3 number4 number5 number6 number7 env_vars