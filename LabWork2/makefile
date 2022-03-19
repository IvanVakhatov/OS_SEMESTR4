perror_number2: perror_number2.o
	gcc -o perror_number2 perror_number2.o

perror_number2.o: perror_number2.c main_header.h
	gcc -O0 -g3 -Wall -c perror_number2.c

strerror_example: strerror_example.o
	gcc -o strerror_example strerror_example.o

strerror_example.o: strerror_example.c main_header.h
	gcc -O0 -g3 -Wall -c strerror_example.c

number3: number3.o
	gcc -o number3 number3.o

number3.o: number3.c main_header.h
	gcc -O0 -g3 -Wall -c number3.c

clean:
	@echo "This is a clean action"
	rm -rf strerror_example perror_number2 number3 *.o

all: perror_number2 strerror_example number3