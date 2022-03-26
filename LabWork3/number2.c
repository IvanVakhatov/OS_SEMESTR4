#include "main_header.h"

#define READ_LENGTH 1000
char buffer[READ_LENGTH];

int main() {
    ssize_t num_read = 1;
    while (num_read != 0) {
        num_read = read(STDIN_FILENO, buffer, READ_LENGTH);
        if(strchr(buffer, 'q') != NULL) {
            exit(EXIT_SUCCESS);
        }
        write(STDOUT_FILENO, buffer, READ_LENGTH);
        buffer[num_read] = '\0';
    }
    return 0;
}