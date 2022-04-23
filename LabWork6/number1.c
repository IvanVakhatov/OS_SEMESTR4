#include "main_header.h"

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void* sortSequence(void* p) {
    int fd, file_size, count;
    const char separator[1] = " ";
    char *temp;

    fd = *((int*)(p));
    file_size = lseek(fd, -1, SEEK_END);
    if (file_size == -1) {
		perror("Lseek error: ");
		pthread_exit((void*)-1);
	}

    lseek(fd, 0, SEEK_SET);
    char buffer[file_size + 1];
    read(fd, &buffer, file_size + 1);
    write(STDOUT_FILENO, &buffer, file_size + 1);
    printf("\n");

    int num_array[file_size];
    for (int i = 0; i < file_size; i++) {
        num_array[i] = 0;
    }

    count = 0;
    temp = strtok(buffer, separator);
	while(temp != NULL)
	{
        num_array[count] = atoi(temp);
        count++;
		temp = strtok(NULL, separator);
	}

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (num_array[j] > num_array[j + 1]) {
                swap(&num_array[j], &num_array[j + 1]);
            }                
        }
    }

    for (int i = 0; i < count; i++) {
        printf("%d ", num_array[i]);
    }

    pthread_exit((void*)0);
}

int main() {
    pthread_t process_command_thread;
    int fd, ret;

    fd = open("digits.txt", O_RDONLY);
    if (fd == -1) {
        perror("Open base file error: ");
        return 1;
    }

    ret = pthread_create(&process_command_thread, NULL, sortSequence, &fd);
    if (ret != 0) {
        perror("Pthread_create error: ");
        return 1;
    }

    pthread_join(process_command_thread, (void*)&ret);
    printf("\nJOIN ret thread value [%d]\n", ret);
    pthread_detach(pthread_self());

    if (close(fd) == -1) {
		perror("Close file error: ");
		return 1;
	}

    return 0;
}