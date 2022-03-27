#include "main_header.h"
#define READ_LENGTH 1024

int main(int argc, char* argv[]) {
    char buffer[READ_LENGTH];
    //char buffer_backwards[READ_LENGTH];
    //ssize_t count;
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Open base file error: ");
        return 1;
    }
    read(fd, buffer, sizeof(buffer));
    write(STDOUT_FILENO, buffer, sizeof(buffer));
    /*for (int i = strlen(buffer); i > 0; i--) {
        printf("%d\n", i);
        buffer_backwards[i] = buffer[READ_LENGTH - i];
    }*/
    //write(STDOUT_FILENO, buffer_backwards, READ_LENGTH);
    close(fd);
    return 0;
}