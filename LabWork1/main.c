#include "main_header.h"
#include "func1.h"
#include "func2.h"

int main(int argc, char *argv[]){
    printf("This is a main file %d\n", MAX_VALUES);
    (void)func1();
    (void)func2();

    int a = 1;
    int b = 2;
    int c = a + b;
    printf("DEBUG: %d\r\n", c);

    return 0;
}