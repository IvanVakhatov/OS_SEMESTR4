#include "main_header.h"

/*int main() {
    extern char** environ;
    while (*environ != NULL) {
        printf("%s\n", *environ);
        environ++;
    }
}*/

int main(int argc, char* argv[], char* envp[]) {
    do {
        if (*envp != NULL) {
            printf("%s\n", *envp);
        }
        else {
            break;
        }
        envp++;
    } while (envp != NULL);
}