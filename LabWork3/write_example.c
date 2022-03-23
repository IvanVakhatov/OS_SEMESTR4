#include "main_header.h"

#define MAX_READ 20

int main() {
    char buffer[MAX_READ] = {'\0'};
    snprintf(buffer, MAX_READ, "%s", "THIS IS LINE\n");
    write(STDOUT_FILENO, buffer, MAX_READ);
    return 0;
}