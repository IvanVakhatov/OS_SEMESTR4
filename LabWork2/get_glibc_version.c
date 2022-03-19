#include <gnu/libc-version.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
    printf("Установленная версия glibc: %s\n", gnu_get_libc_version());
    printf("Текущий выпуск glibc: %s\n", gnu_get_libc_release());
    exit(EXIT_SUCCESS);
}