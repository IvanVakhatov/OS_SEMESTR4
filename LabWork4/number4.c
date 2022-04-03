#include "main_header.h"

#define MAX_LENGTH 1000
#define NUM_STRINGS 1000
extern char** environ;

int main() {
    int var_num, count = 0;
    char env_vars[NUM_STRINGS][MAX_LENGTH] = {""};
    const char separator[1] = "=";
    char *temp;

    while (environ[count] != NULL) {
        strcpy(env_vars[count], environ[count]);
        count++;
    }
    printf("%-5s%-35s%-30s\n", "#", "Environment_Variable", "Value");
    for (int i = 0; i < count; i++) {
        temp = strtok(env_vars[i], separator);
        printf("%-5d%-35s", i, temp);
        temp = strtok(NULL, separator);
        printf("%-30s\n", temp);
    }

    printf("Введите номер переменной, которую вы хотите удалить: ");
    scanf("%d", &var_num);
    unsetenv(env_vars[var_num]);
    count = 0;

    while (environ[count] != NULL) {
        strcpy(env_vars[count], environ[count]);
        count++;
    }
    printf("%-5s%-35s%-30s\n", "#", "Environment_Variable", "Value");
    for (int i = 0; i < count; i++) {
        temp = strtok(env_vars[i], separator);
        printf("%-5d%-35s", i, temp);
        temp = strtok(NULL, separator);
        printf("%-30s\n", temp);
    }
    exit(EXIT_SUCCESS);
}