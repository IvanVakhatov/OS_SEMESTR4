#ifndef HDR_H
#define HDR_H /* Предотвращает случайное двойное включение */
#define CWDSIZE 256
#define BASHCOMMANDSIZE 33
#include <sys/types.h> /* Определения типов, используемые многими
программами */
#include <stdio.h> /* Стандартные функции ввода-вывода */
#include <stdlib.h> /* Прототипы наиболее востребованных библиотечных
функций плюс константы EXIT_SUCCESS и EXIT_FAILURE */
#include <unistd.h> /* Прототипы многих системных вызовов */
#include <fcntl.h> /* Управление файлами и работа
с файловыми дескрипторами */
#include <errno.h> /* Объявление errno и определение констант ошибок */
#include <string.h> /* Наиболее используемые функции обработки строк */
#include <signal.h>
#include <pthread.h>
#include <sys/wait.h>
#include <limits.h>
#include <ctype.h>
typedef enum { FALSE, TRUE } Boolean;
#endif