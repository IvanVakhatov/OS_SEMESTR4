#include "main_header.h"

#define READ_LENGTH 1000
char buffer[READ_LENGTH];

int main(int argc, char* argv[]) {
    int cp_from, cp_to;
    cp_from = open(argv[1], O_RDONLY | S_IRUSR, S_IWUSR);
    if (cp_from == -1) {
        perror("Open base file error: ");
        return 1;
    }
    cp_to = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (cp_to == -1) {
        perror("Open destination file error: ");
        return 1;
    }
    read(cp_from, buffer, sizeof(buffer));
    write(cp_to, buffer, sizeof(buffer));
    close(cp_from);
    close(cp_to);
    return 0;
}