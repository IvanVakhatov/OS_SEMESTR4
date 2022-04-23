pthread_ex: pthread_ex.o
	gcc -o pthread_ex pthread_ex.o -pthread

pthread_ex.o: pthread_ex.c main_header.h
	gcc -O0 -g3 -Wall -c pthread_ex.c -pthread

thread_join_ex: thread_join_ex.o
	gcc -o thread_join_ex thread_join_ex.o -pthread

thread_join_ex.o: thread_join_ex.c main_header.h
	gcc -O0 -g3 -Wall -c thread_join_ex.c -pthread

number1: number1.o
	gcc -o number1 number1.o -pthread

number1.o: number1.c main_header.h
	gcc -O0 -g3 -Wall -c number1.c -pthread

number2: number2.o
	gcc -o number2 number2.o

number2.o: number2.c main_header.h
	gcc -O0 -g3 -Wall -c number2.c

number3: number3.o
	gcc -o number3 number3.o

number3.o: number3.c main_header.h
	gcc -O0 -g3 -Wall -c number3.c

clean:
	@echo "This is a clean action"
	rm -rf pthread_ex thread_join_ex number1 *.o
	
all: pthread_ex thread_join_ex number1