perror_example: perror_example.o
	gcc -o perror_example perror_example.o

perror_example.o: perror_example.c main_header.h
	gcc -O0 -g3 -Wall -c perror_example.c

strerror_example: strerror_example.o
	gcc -o strerror_example strerror_example.o

strerror_example.o: strerror_example.c main_header.h
	gcc -O0 -g3 -Wall -c strerror_example.c

clean:
	@echo "This is a clean action"
	rm -rf strerror_example perror_example *.o

all: perror_example strerror_example