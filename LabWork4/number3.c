#include "main_header.h"

const char *my_var = NULL;
extern char** environ;

int main (int argc, char *argv[]) {
    my_var = argv[1];
    int count = 0;

    if (strcmp(my_var, "SOMEVAR") == 0) {
        while (environ[count] != NULL) {
            printf("%s\n", environ[count]);
            count++;
        }
    }
    else if (strcmp(my_var, "SOMEVAR=VAR") == 0) {
        if (setenv("SOMEVAR", "VAR", 0) == -1) {
            perror("Setenv error: ");
            return 1;
        }
        else {
            while (environ[count] != NULL) {
                printf("%s\n", environ[count]);
                count++;
            }
        }
    }
    exit(EXIT_SUCCESS);
}