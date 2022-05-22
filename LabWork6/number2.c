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
    int iret, count = 0;

    //for((i=1;i<=50000;i++)); do echo -n $(($RANDOM))" "; done > digits2.txt");

    fd = open("digits2.txt", O_RDONLY);
    if (fd == -1) {
        perror("Open base file error: ");
        return 1;
    }

    ret = pthread_create(&process_command_thread, NULL, sortSequence, &fd);
    if (ret != 0) {
        perror("Pthread_create error: ");
        return 1;
    }

    label: iret = pthread_tryjoin_np(process_command_thread, NULL);

    if ((iret != 0) && (iret != EBUSY)) {
        perror("Pthread_tryjoin_np error: ");
        return 1;
    }
    else if (iret == EBUSY) {
        if (count == 5) {
            printf("Поток занят, завершение работы.\n");
            return 1;
        }
        printf("Попытка номер: %d\n", count + 1);
            
        if (usleep(1000000) == -1) {
            perror("Usleep error: ");
            return 1;
        }

        count++;
        goto label;
    }

    if (iret == 0) {
        printf("\n\nОтлично!\n");
    }
    
    printf("JOIN ret thread value [%d]\n", ret);
    pthread_detach(pthread_self());

    if (close(fd) == -1) {
		perror("Close file error: ");
		return 1;
	}

    return 0;
}