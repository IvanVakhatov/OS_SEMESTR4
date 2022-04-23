#include "main_header.h"

pthread_t h_process_command_thread, h_main_thread;

void* process_command_thread(void* p) {
    int cycles = 10;
    printf("Hello from process command thread %lu\n", pthread_self());
    for (int i = 0; i < cycles; i++) {
        printf("Process command thread cycle [%d]\n", i);
    }
    pthread_exit((void*)0);
}

int main() {
    int h_process_command_thread_initialized;
    int ret;
    
    ret = pthread_create(&h_process_command_thread, NULL, process_command_thread, NULL);
    if (ret != 0) {
        printf("ERROR: pthread_create failed [%d]\n", ret);
        return 1;
    }

    h_process_command_thread_initialized = 1;
    printf("Command thread [%lu]\n", h_process_command_thread);
    printf("Main thread [%lu]\n", pthread_self());

    if (pthread_equal(h_process_command_thread, pthread_self()) == 0) {
        printf("Threads are not equal\n");
    }
    
    pthread_join(h_process_command_thread, (void*)&ret);
    printf("JOIN ret thread value [%d]\n", ret);

    pthread_detach(pthread_self());
    return 0;
}