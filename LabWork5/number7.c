#include "main_header.h"
int status;

int main(int argc, char* argv[], char* envp[]) {
	pid_t pid = fork();
    
    if (pid == -1) {
        perror("Fork error: ");
    }
    else if (pid == 0) {
        if (execvp("./env_vars", argv) == -1) {
            perror("Execvp error: ");
        }
    }
    else {
        if (waitpid(pid, &status, 0) == -1) {
            perror("Waitpid error");
            exit(EXIT_FAILURE);
        }
        printf("\nChild process return value: %s\n",
                (WIFEXITED(status) ? "Success" : "Failure"));
    }
    return 0;
}