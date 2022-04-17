#include "main_header.h"

int main(int argc, char* argv[]) {
    pid_t pid = fork();
    
    if (pid == -1) {
        perror("Fork error: ");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        printf("This is child. PID: %d; Parent's PID: %d\n", getpid(), getppid());
    }
    else {
        printf("This is parent. PID: %d; Parent's PID: %d\n", getpid(), pid);
    }
    exit(EXIT_SUCCESS);
}