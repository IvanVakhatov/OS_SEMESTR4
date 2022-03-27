#include "main_header.h"

#define READ_LENGTH 1024
char buffer[READ_LENGTH];

int main(int argc, char* argv[]) {
    int fd, up = 0, down = 0;
    char temp;

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Open base file error: ");
        return 1;
    }
    read(fd, buffer, sizeof(buffer));
    write(STDOUT_FILENO, buffer, sizeof(buffer));
    write(STDOUT_FILENO, "\n", 1);
    
    down = strlen(buffer) - 1;
    while (up < down) {
        temp = buffer[down];  
        buffer[down] = buffer[up];
        buffer[up] = temp;  
        up++;
        down--; 
    }
    write(STDOUT_FILENO, buffer, sizeof(buffer));
    write(STDOUT_FILENO, "\n", 1);
    close(fd);
    return 0;
}