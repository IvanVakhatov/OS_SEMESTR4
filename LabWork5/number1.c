#include "main_header.h"

int main(int argc, char* argv[]) {
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("Fork error: ");
    }
    else if (pid == 0) {
        printf("This is child. PID: %d\n", getpid());
    }
    else {
        printf("This is parent. PID: %d\n", getpid());
    }
    return 0;
}