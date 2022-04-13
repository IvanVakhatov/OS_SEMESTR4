#include "main_header.h"

static int idata = 111;
int main(int argc, char* argv[]) {
    int istack = 222; /* Выделена в сегменте стека */
    pid_t childPid;
    switch (childPid = fork()) {
        case -1:
            perror("Fork error:");
            exit(EXIT_FAILURE);
        case 0:
            idata *= 3;
            istack *= 3;
            break;
        default:
            sleep(3); /* Даем потомку шанс выполниться */
            break;
    }
    /* Здесь выполняются и потомок и родитель */
    printf("PID=%ld %s idata=%d istack=%d\n", (long)getpid(),
        (childPid == 0) ? "(child) " : "(parent)", idata, istack);
    exit(EXIT_SUCCESS);
}