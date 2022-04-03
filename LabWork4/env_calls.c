#include "main_header.h"
extern char** environ;

int main(int argc, char* argv[], char* envp[]) {
    int j;
    char** ep;
    clearenv(); /* Удаление всей среды */
    for (j = 1; j < argc; j++) {
        if (putenv(argv[j]) != 0) {
            printf("ERROR: putenv %s\n", argv[j]);
            return 1;
        }
    }
    //if (setenv("VAR", "Hello world", 0) == -1) {
    if (setenv("BYE", "Hello world", 0) == -1) {
        perror("Setenv: ");
        return 1;
    }
    for (ep = environ; *ep != NULL; ep++) {
        puts(*ep);
    }
    printf("/-----/\n");
    unsetenv("BYE");
    for (ep = environ; *ep != NULL; ep++) {
        puts(*ep);
    }
    exit(EXIT_SUCCESS);
}