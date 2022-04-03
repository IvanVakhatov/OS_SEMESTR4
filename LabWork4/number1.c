#include "main_header.h"

int main(void) {
    int pid_t = getpid();
    int ppid_t = getppid();
    printf("PID is: %d\n", pid_t);
    printf("Parrent PID is: %d\n", ppid_t);
    return 0;
}