#include "main_header.h"

int main(int argc, char* argv[]) {
    pid_t pid = fork();
    
    if (pid == 0) {
        printf("This is child. PID: %d; Parent's PID: %d\n", getpid(), getppid());
    }
    else {
        printf("This is parent. PID: %d; Parent's PID: %d\n", getpid(), pid);
    }
    return 0;
}