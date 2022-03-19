#include "main_header.h"

int main (int argc, char *argv[]) {
    int index, end_count = 134;
    printf("Номер ошибки | Описание ошибки\n");
    for (index = 1; index < end_count; index++) {
        if (index < 10) {
            printf("%d%12s| %s\n", index, " ", strerror(index));
        }
        else if (index < 100){
            printf("%d%11s| %s\n", index, " ", strerror(index));
        }
        else {
            printf("%d%10s| %s\n", index, " ", strerror(index));
        }
    }
   return(0);
}