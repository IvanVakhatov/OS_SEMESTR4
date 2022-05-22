#ifndef HDR_H
#define HDR_H /* Предотвращает случайное двойное включение */

#define LINUX_PROC_TASK_PATH "/proc"
#define LINUX_PROC_STAT_PATH "/stat"

#include <stdio.h> /* Стандартные функции ввода-вывода */
#include <stdlib.h> /* Прототипы наиболее востребованных библиотечных
функций плюс константы EXIT_SUCCESS и EXIT_FAILURE */
#include <unistd.h> /* Прототипы многих системных вызовов */
#include <string.h> /* Наиболее используемые функции обработки строк */
#include <linux/limits.h>
#include <sys/eventfd.h>
#include <sys/poll.h>
#include <pthread.h>
#include <poll.h>
#include <dirent.h>
#include <stdbool.h>
#include <ctype.h>

#endif
