open_example: open_example.o
	gcc -o open_example open_example.o

open_example.o: open_example.c main_header.h
	gcc -O0 -g3 -Wall -c open_example.c

read_example: read_example.o
	gcc -o read_example read_example.o

read_example.o: read_example.c main_header.h
	gcc -O0 -g3 -Wall -c read_example.c

write_example: write_example.o
	gcc -o write_example write_example.o

write_example.o: write_example.c main_header.h
	gcc -O0 -g3 -Wall -c write_example.c

number1: number1.o
	gcc -o number1 number1.o

number1.o: number1.c main_header.h
	gcc -O0 -g3 -Wall -c number1.c

clean:
	@echo "This is a clean action"
	rm -rf open_example read_example write_example number1 *.o

all: open_example read_example write_example number1