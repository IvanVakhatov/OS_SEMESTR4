#include "main_header.h"

#define MAX_READ 20
char buffer[MAX_READ];

int main() {
    ssize_t numRead;
    numRead = read(STDIN_FILENO, buffer, MAX_READ);
    if (numRead == -1) {
        perror("Read: ");
        return 1;
    }
    buffer[numRead] = '\0';
    printf("The input data was: %s\n", buffer);
}