#include "main_header.h"

void csv_preparation(char csv_name[]) {
    // Указатель на csv файл, в который будут записаны данные
    FILE *csv_file;

    // Открытие csv файла
    csv_file = fopen(csv_name, "a+");
    if (csv_file == NULL) {
        return;
    }
    // Подготовка - запись подписей столбцов
    fprintf(csv_file, "%s,%s,%s,%s,%s,", "pid", "comm", "state", "ppid", "pgrp");
    fprintf(csv_file, "%s,%s,%s,%s,%s,", "session", "tty_nr", "tpgid", "flags", "minflt");
    fprintf(csv_file, "%s,%s,%s,%s,%s,", "cminflt", "majflt", "cmajflt", "utime", "stime");
    fprintf(csv_file, "%s,%s,%s,%s,%s,", "cutime", "cstime", "priority", "nice", "num_threads");
    fprintf(csv_file, "%s,%s,%s,%s,%s\n", "itrealvalue", "starttime", "vsize", "rss", "rsslim");

    // Закрытие файлового дескриптора
    fclose(csv_file);
    return;
}

void get_pid_stat(int pid_number, char csv_name[]) {
    // Указатель на csv файл, в который будут записаны данные
    FILE *csv_file;
    // Указатель на файл, в котором хранится статистика процесса
    FILE *pid_file;
    // Счетчик кол-ва параметров
    int count = 0;

    // Выделение памяти для хранения пути к файлу stat данного pid
    char file_path[PATH_MAX];
    // Формирование полного пути к файлу - копированием строк переменную
    int len = snprintf(file_path, sizeof file_path, "%s/%d%s", LINUX_PROC_TASK_PATH, pid_number, LINUX_PROC_STAT_PATH);
    if (len < 0 || (unsigned) len >= sizeof file_path) {
        return;
    }

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
    return;
}

void write_pids_stat() {
    DIR * dir_stream = NULL;
	struct dirent * procfs_entry = NULL;
	dir_stream = opendir(LINUX_PROC_TASK_PATH);
	pid_t pid;

	if(dir_stream == NULL) {
		perror("opendir");
	}

	while((procfs_entry = readdir(dir_stream)) != NULL) {
		char *sym;
		bool acceptable_name = true;
		for(sym = procfs_entry->d_name; *sym; sym++) {
			if(isdigit(*sym) == 0) {
				acceptable_name = false;
				break;
			}
		}
		if(acceptable_name == false) {
			continue;
		}
	
		pid = (pid_t)atoi(procfs_entry->d_name);
		if(pid <= 0) {
			continue;
		}
        get_pid_stat(pid, "proc_stat.csv");
	}
	(void)closedir(dir_stream);
    return;
}

int main(int argc, char *argv[]) {
    csv_preparation("proc_stat.csv");
    write_pids_stat();
    printf("Генерирование csv файла со статистическими данными завершено!\n");
    return 0;
}
