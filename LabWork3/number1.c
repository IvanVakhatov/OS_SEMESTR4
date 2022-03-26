#include "main_header.h"

int main() {
    int fd;
    //fd = 450;
    fd = 0;
    printf("File descriptor after initialization: %d\n", fd);
    close(fd);
    printf("File descriptor after closing: %d\n", fd);
    fd = open("startup.txt", O_RDONLY);
    printf("File descriptor after 'open' method: %d\n", fd);
    return 0;
}