#include "main_header.h"
#include <pthread.h>

void* process_command_thread(void* p) {
    int cycles = 10;
    printf("Hello from process command thread %lu\n", pthread_self());

    for (int i = 0; i < cycles; i++) {
        printf("Process command thread cycle [%d]\n", i);
    }
    pthread_exit((void*)0);
}

int main() {
    pthread_t h_process_command_thread;
    int ret;

    ret = pthread_create(&h_process_command_thread, NULL, process_command_thread, NULL);
    if (ret != 0) {
        printf("ERROR: pthread_create failed [%d]\n", ret);
        return -1;
    }

    printf("Hello from main thread\n");
    return 0;
}