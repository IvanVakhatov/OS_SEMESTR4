#include "main_header.h"

void* process_command(void* p) {
    printf("Hello from process command thread %lu\n\n", pthread_self());
    pthread_exit((void*)0);
}

int main(int argc, char* argv[]) {
    pthread_attr_t tattr;
	int ret, iret, returnedValue = 42;
	pthread_t process_command_thread;

    ret = pthread_attr_init(&tattr);
	if (ret != 0) {
		printf("ERROR: pthread_attr_init failed [%d]\n", ret);
		return 1;
	}

	/* set the thread detach state */
    ret = pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_DETACHED);

	iret = pthread_create(&process_command_thread, &tattr, process_command, NULL);
    if (iret != 0) {
        printf("ERROR: pthread_create failed [%d]\n", iret);
        return 1;
    }

	pthread_attr_destroy(&tattr);
    
    pthread_join(process_command_thread, (void*) &returnedValue);
	printf("Returned value = %d\n", returnedValue);

	iret = pthread_create(&process_command_thread, NULL, process_command, NULL);
    if (iret != 0) {
        printf("ERROR: pthread_create failed [%d]\n", iret);
        return 1;
    }

	pthread_join(process_command_thread, (void*) &returnedValue);
    printf("Returned value = %d\n", returnedValue);

	return 0;
}