#include "main_header.h"

void func(void) {
    printf("Child process exit action\n");
}

int main(int argc, char* argv[]) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork error: ");
    }
    else if (pid == 0) {
        printf("This is child. PID: %d\n", getpid());
        if (atexit(func) != 0) {
            perror("At_exit error: ");
        }
    }
    else {
        printf("This is parent. PID: %d\n", getpid());
    }
    return 0;
}