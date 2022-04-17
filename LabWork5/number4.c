#include "main_header.h"
int status;

int main(int argc, char* argv[]) {
    pid_t pid = fork();
        
    if (pid == -1) {
        perror("Fork error: ");
    }
    else if (pid == 0) {
        printf("This is child. PID: %d\n", getpid());
        //kill(getpid(), SIGKILL);
    }
    else {
        if (waitpid(pid, &status, 0) == -1) {
            perror("Waitpid error: ");
        }

        printf("This is parent. PID: %d\n", getpid());

        if (WIFEXITED(status)) {
            printf("Child exited, status = %d\n", WEXITSTATUS(status));
        }
		printf("Child killed by a signal?: %s\n", (WIFSIGNALED(status) ? "True" : "False"));
        printf("Child stopped by a signal?: %s\n", (WIFSTOPPED(status) ? "True" : "False"));
        printf("Child resumed by a signal? %s\n", (WIFCONTINUED(status) ? "True" : "False"));
    }
    return 0;
}