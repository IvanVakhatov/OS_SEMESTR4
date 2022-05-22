#include "main_header.h"

void generate_pids_file(char file_name[], char csv_name[]) {
    // Указатель на csv файл, в который будут записаны данные
    FILE *csv_file;
    // Указатель на файл, который вызывает команду в оболочке shell
    FILE *bash_cmnd_exec;

    // Выделение памяти под хранение текста исполняемой команды bash
    char *exec_bash_command = malloc(sizeof(char) * (BASHCOMMANDSIZE+CWDSIZE+strlen(file_name)));
    // Хранение пути текущей рабочей директории
    char cwd[CWDSIZE];
    // Основной текст исполняемого скрипта bash
    char bash_command[] = "ls /proc | grep -E '^[0-9]+$' > ";
    // Запись абсолютного пути текущего рабочего каталога в массив, на который указывает перем. cwd
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        // Если не удалось получить путь - вывести ошибку и завершить работу досрочно
        perror("Getcwd() error");
        exit(EXIT_FAILURE);
    }

    // Формирование полного текста скрипта bash путем копирования частей в переменную
    strcat(exec_bash_command, bash_command);
    strcat(exec_bash_command, cwd);
    strcat(exec_bash_command, file_name);

    // Создание потока вызова команды в оболочке
    bash_cmnd_exec = popen(exec_bash_command, "r");
    if (bash_cmnd_exec == NULL) {
        // Если не удалось выполнить команду - вывести сообщение и завершить работу досрочно
        printf("Failed to run bash command\n" );
        exit(EXIT_FAILURE);
    }

    //Открытие csv файла со статистикой и запись заголовков столбцов
    csv_file = fopen(csv_name, "a+");
    if (csv_file == NULL) {
        return;
    }
    fprintf(csv_file, "%s,%s,%s,%s,%s,", "pid", "comm", "state", "ppid", "pgrp");
    fprintf(csv_file, "%s,%s,%s,%s,%s,", "session", "tty_nr", "tpgid", "flags", "minflt");
    fprintf(csv_file, "%s,%s,%s,%s,%s,", "cminflt", "majflt", "cmajflt", "utime", "stime");
    fprintf(csv_file, "%s,%s,%s,%s,%s,", "cutime", "cstime", "priority", "nice", "num_threads");
    fprintf(csv_file, "%s,%s,%s,%s,%s\n", "itrealvalue", "starttime", "vsize", "rss", "rsslim");
    fclose(csv_file);

    // Закрытие потока, открытый ранее popen
    pclose(bash_cmnd_exec);
    // Высвобождение ресурсов памяти переменной exec_bash_command
    free(exec_bash_command);
    return;
}

void get_pid_stat(int pid_number, char csv_name[]) {
    // Указатель на csv файл, в который будут записаны данные
    FILE *csv_file;
    // Указатель на файл, в котором хранятся все идентификаторы, находящиеся в папке /proc
    FILE *pid_file;
    // Переменная для хранения текущего номера pid
    char pidd[4];
    // Счетчик кол-ва параметров
    int count = 0;

    // Преобразование переменной int - pid_number - в char
    sprintf(pidd, "%d", pid_number);
    // Выделение памяти для хранения пути к файлу stat данного pid
    char *file_path = malloc(sizeof(char) * (6 + 5 + strlen(pidd)));
    // Формирование полного пути к файлу - копированием строк переменную
    strcat(file_path, "/proc/");
    strcat(file_path, pidd);
    strcat(file_path, "/stat");

    // Открытие файла по ранее созданному пути
    pid_file = fopen(file_path, "r");
    if (pid_file == NULL) {
        // В случае ошибки - выйти из функции досрочно
        return;
    }
    else {
        // Иначе - открытие файла csv_name
        csv_file = fopen(csv_name, "a+");
        if (csv_file == NULL) {
            // В случае ошибки - досрочный выход из функции
            return;
        }
        // Бесконечный цикл
        while (42) {
            // Переменная для хранения строки, содержащую параметр
            char line[100];
            char *parameter;
            // Разделитель для файла - пробел
            char *separator = " ";

            // Если считанная строка содержит пустоту (EOF)
            if (fgets(line, 100, pid_file) == NULL) {
                //printf("%s", "\n");

                // Запись в csv файл символа новой строки
                fprintf(csv_file, "%s", "\n");
                // Выход из цикла
                break;
            }
            // Разделение строки с помощью ранее объявленного разделителя
            parameter = strtok(line, separator);
            while (parameter) {
                // Запись в csv файл 25 первых парамтеров из файла /proc/pid/stat
                if (count < 25) {
                    //printf("%s,", parameter);
                    // Запись в csv файл очередной параметр
                    fprintf(csv_file, "%s,", parameter);
                    // Увеличение счетчика параметров на 1
                    count++;
                }
                parameter = strtok(NULL, separator);
            }
        }
        // Закрытие файлового потока csv файла
        fclose(csv_file);
    }
    // Закрытие файлового потока файла с pid'ами
    fclose(pid_file);
    // Высвобождение ресурсов памяти переменной file_path
    free(file_path);
    return;
}

void get_pids_stat(char csv_name[], int pid_num) {
    // Указатель на файл, в котором хранятся все идентификаторы, находящиеся в папке /proc
    FILE *file;
    // Счетчик кол-ва pid'ов в файле
    int count = 0;
    // Массив для считанных pid'ов
    int numbers[1000];

    // Открытие файла для считывания pid'ов
    file = fopen("pids.txt", "r");
        if (file == NULL) {
        // В случае ошибки - выйти из функции досрочно
        return;
    }
    
    // Прока не будет достигнут конец файла (EOF)
    // Запись в массив номера pid
    while (fscanf(file, "%d", &numbers[count]) != EOF) {
        // Увеличение счетчика кол-ва pid'ов в файле на 1
        count++;
    }
    // Добавления спец символа в массив pid'ов, чтобы знать, когда закончить итерацию по массиву
    numbers[count] = '\0';
    // Итерация по массиву pid'ов
    for (int i = 0; numbers[i] != '\0'; i++) {
        /* Проверка номера pid'а - если больше pid'a программы, то процесс запущен во время выполнения
           программы и не может быть считан*/
        if (numbers[i] < pid_num) {
            // Иначе - вызвать фун-ию get_pid_stat для текущего pid'а
            get_pid_stat(numbers[i], csv_name);
        }
    }
    // Закрытие файлового потока файла с pid'ами
    fclose(file);
    return;
}

int main(int argc, char *argv[]) {
    char file_name[20];
    strcpy(file_name, "proc_stat.csv");

    int number = getpid();
    printf("PID: %d\n", number);

    generate_pids_file("/pids.txt", file_name);
    get_pids_stat(file_name, number);
    printf("Генерирование csv файла со статистическими данными завершено!\n");
    return 0;
}
