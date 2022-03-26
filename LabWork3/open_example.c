#include "main_header.h"

int main() {
    /* Открытие существующего файла для чтения */
    int fd = open("startup.txt", O_RDONLY);
    if (fd == -1) {
        perror("Open startup file: ");
        return 1;
    }
    /* Открытие нового или существующего файла для чтения и записи с
    усечением до нуля байтов; предоставление владельцу исключительных прав
    доступа на чтение и запись */
    fd = open("myfile.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Open myfile: ");
        return 1;
    }
    /* Открытие нового или существующего файла для записи; записываемые данные
    должны всегда добавляться в конец файла */
    fd = open("w.log", O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Open w.log file: ");
        return 1;
    }
    /* FOR THE RECORD: int creat(const char *pathname, mode_t mode) ==
    fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode); */
    if (fd >= 0) {
        if (close(fd) == -1) {
            perror("Close: ");
            return 1;
        }
    }
    fd = -1;
    return 0;
}