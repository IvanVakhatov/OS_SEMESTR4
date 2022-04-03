#include "main_header.h"

extern char etext, edata, end;

int main() {
    int init_block_size;
    int uninit_block_size;
    printf("Адрес текста программы (etext): %p\n", &etext);
    printf("Адрес блока инициализированных данных (edata): %p\n", &edata);
    printf("Адрес блока неинициализированных данных (end): %p\n", &end);

    init_block_size = &edata - &etext;
    uninit_block_size = &end - &edata;
    printf("\nРазмер блока инициализированных данных: %d\n", init_block_size);
    printf("Размер блока неинициализированных данных: %d\n", uninit_block_size);
    exit(EXIT_SUCCESS);
}