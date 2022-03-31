#include "main_header.h"

int main(int argc, char* argv[]) {
    int fd, file_size;
    char buffer;
    /* int a = 123123;
    void* num = &a;
    printf("%d\n",*((int*)(num))); */
    
    //*(([тип])([имя]))

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Open base file error: ");
        return 1;
    }

    file_size = lseek(fd, -1, SEEK_END);
    while (file_size >= 0) {
        read(fd, &buffer, 1);
        write(STDOUT_FILENO, &buffer, 1);
        file_size = lseek(fd, -2, SEEK_CUR);
    }
    write(STDOUT_FILENO, "\n", 1);
    close(fd);
    return 0;
}