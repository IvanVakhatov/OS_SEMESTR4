#include "main_header.h"

int main(void) {
    int number, pid_t = getpid();
    int ppid_t = getppid();
    printf("PID is: %d\n", pid_t);
    printf("Parrent PID is: %d\n", ppid_t);
    scanf("%d", &number);
    exit(EXIT_SUCCESS);
}