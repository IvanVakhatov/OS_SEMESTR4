#include "main_header.h"

int main(int argc, char* argv[]) {
	pid_t child_pid;
	printf("Parent PID = %ld\n", (long)getpid());

	switch (child_pid = fork()) {
		case -1:
			perror("Fork error: ");
			exit(EXIT_FAILURE);
            break;
		case 0:
			printf("Child PID  = %ld\n", (long)getpid());
			exit(EXIT_SUCCESS);
            break;
		default:
			sleep(3);
			printf("ps system call:\n");
			system("ps");
			if (kill(child_pid, SIGKILL) == -1) {
				perror("Kill error: ");
				exit(EXIT_FAILURE);
			}
			printf("\n");
			sleep(3);
			printf("ps system call after a kill signal:\n");
			system("ps");

			if (waitpid(child_pid, NULL, 0) == -1) {
				perror("Waitpid error: ");
				exit(EXIT_FAILURE);
			}

			printf("\n");
			sleep(3);
			printf("ps system call after waitpid:\n");
			system("ps");

			exit(EXIT_SUCCESS);
            break;
	}
	return 0;
}