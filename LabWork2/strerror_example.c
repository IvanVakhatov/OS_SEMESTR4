#include "main_header.h"

int main (int argc, char *argv[]) {
   /* Инициализация File Descriptor'а (целое число, которое однозначно
   идентифицирует открытый файл процесса) */
   int fd;
   // Открытие файла с атрибутом read_only
   fd = open("test_file.txt", O_RDONLY);
   // Если возникла ошибка при открытии файла
   if (fd == -1) {
      printf("Error: %s\n", strerror(errno));
      exit(EXIT_FAILURE);
   }
   // Иначе - вывести номер дескриптора
   else {
      printf("File descriptor = %d\n", fd);
   }
   return(0);
}