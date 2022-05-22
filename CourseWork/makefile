generate_stat_csv: generate_stat_csv.o
	gcc -o generate_stat_csv generate_stat_csv.o

generate_stat_csv.o: generate_stat_csv.c main_header.h
	gcc -O0 -g3 -Wall -c generate_stat_csv.c

clean:
	@echo "This is a clean action"
	rm -rf generate_stat_csv pids.txt proc_stat.csv *.o
	
all: generate_stat_csv