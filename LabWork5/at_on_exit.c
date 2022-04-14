#define _GNU_SOURCE_
#include "main_header.h"

static void atExitFunc1(void) {
    printf("at_exit function 1 is called\n");
}

static void atExitFunc2(void) {
    printf("at_exit function 2 is called\n");
}

static void onExitFunc(int exitStatus, void* arg) {
    printf("on_exit function is called: status=%d, arg=%ld\n",
            exitStatus, (long)arg);
}

int main(int argc, char* argv[]) {
    if (on_exit(onExitFunc, (void*)10) != 0) {
        perror("on_exit 1");
    }
    if (atexit(atExitFunc1) != 0) {
        perror("at_exit 1");
    }
    if (atexit(atExitFunc2) != 0) {
        perror("at_exit 2");
    }
    if (on_exit(onExitFunc, (void*)20) != 0) {
        perror("on_exit 2");
    }
    exit(2);
}