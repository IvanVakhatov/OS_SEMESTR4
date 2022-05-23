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

void get_pid_stat(int pid_number, char csv_name[], char cpu_stat[]) {
    // Указатель на csv файл, в который будут записаны данные
    FILE *csv_file;
    // Указатель на файл, в котором хранится статистика процесса
    FILE *pid_file;
    FILE *uptime_file;

    bool get_cpu_stat;
    int PROCESS_UTIME, PROCESS_STIME, PROCESS_STARTTIME, SYSTEM_UPTIME_SEC;
    int PROCESS_UTIME_SEC, PROCESS_STIME_SEC, PROCESS_STARTTIME_SEC;
    int PROCESS_ELAPSED_SEC, PROCESS_USAGE_SEC, PROCESS_USAGE;
    if (strcmp(cpu_stat, "yes") == 0) {
        get_cpu_stat = true;
    }
    else {
        get_cpu_stat = false;
    }

    // Выделение памяти для хранения пути к файлу stat данного pid
    char file_path[PATH_MAX];
    // Формирование полного пути к файлу - копированием строк переменную
    int len = snprintf(file_path, sizeof file_path, "%s/%d%s", LINUX_PROC_TASK_PATH, pid_number, LINUX_PROC_STAT_PATH);
    if (len < 0 || (unsigned) len >= sizeof file_path) {
        return;
    }

    char uptime_file_path[PATH_MAX];
    // Формирование полного пути к файлу - копированием строк переменную
    int lenn = snprintf(uptime_file_path, sizeof uptime_file_path, "%s%s", LINUX_PROC_TASK_PATH, LINUX_PROC_UPTIME_PATH);
    if (lenn < 0 || (unsigned) lenn >= sizeof uptime_file_path) {
        return;
    }

    // Открытие файла по ранее созданному пути
    pid_file = fopen(file_path, "r");
    if (pid_file == NULL) {
        // В случае ошибки - выйти из функции досрочно
        return;
    }
    // Иначе - открытие файла csv_name
    else {
        // Счетчик кол-ва параметров
        int count = 0;
        // Переменная для хранения строки, содержащую параметр
        char buffer[128];
        char utime[100];

        if (get_cpu_stat == false) {
            // Открытие csv файла
            csv_file = fopen(csv_name, "a+");
            if (csv_file == NULL) {
                // В случае ошибки - досрочный выход из функции
                return;
            }
            // Запись параметров в файл
            while ((fscanf(pid_file, "%s", buffer) == 1) && (count < 25) ) {
                fprintf(csv_file, "%s,", buffer);
                count++;
            }
            fprintf(csv_file, "%s", "\n");
            fclose(csv_file);
        }
        else {
            // Открытие файла по ранее созданному пути
            uptime_file = fopen(uptime_file_path, "r");
            if (uptime_file == NULL) {
                // В случае ошибки - выйти из функции досрочно
                return;
            }
            if (fscanf(uptime_file, "%s", utime) == 1) {;
                sscanf(utime, "%d", &SYSTEM_UPTIME_SEC);
                //printf("%d ", SYSTEM_UPTIME_SEC);
            }
            while ((fscanf(pid_file, "%s", buffer) == 1) && (count < 25) ) {
                //printf("%s ", buffer);
                if (count == 13) {
                    sscanf(buffer, "%d", &PROCESS_UTIME);
                    //printf("%d ", PROCESS_UTIME);
                }
                if (count == 14) {
                    sscanf(buffer, "%d", &PROCESS_STIME);
                    //printf("%d ", PROCESS_STIME);
                }
                if (count == 21) {
                    sscanf(buffer, "%d", &PROCESS_STARTTIME);
                    //printf("%d ", PROCESS_STARTTIME);
                }
                count++;
            }
            PROCESS_UTIME_SEC = PROCESS_UTIME / CLOCK_TICK;
            PROCESS_STIME_SEC = PROCESS_STIME / CLOCK_TICK;
            PROCESS_STARTTIME_SEC = PROCESS_STARTTIME / CLOCK_TICK;

            PROCESS_ELAPSED_SEC = SYSTEM_UPTIME_SEC - PROCESS_STARTTIME_SEC;
            if (PROCESS_ELAPSED_SEC == 0) {
                PROCESS_USAGE = 0;
            }
            else {
                PROCESS_USAGE_SEC = PROCESS_UTIME_SEC + PROCESS_STIME_SEC;
                PROCESS_USAGE = PROCESS_USAGE_SEC * 100 / PROCESS_ELAPSED_SEC;
            }

            printf("PID процесса: %6d. Он провел: %4d секунд(ы) в пользовательском режиме", pid_number, PROCESS_UTIME_SEC);
            printf(", %4d секунд(ы) в режиме ядра. Общая загрузка CPU: %6d секунд(ы). ", PROCESS_STIME_SEC, PROCESS_USAGE_SEC);
            printf("Процесс запущен уже в течение: %6d секунд(ы). Использование CPU: %4d%c\n", PROCESS_ELAPSED_SEC, PROCESS_USAGE, 37);
            fclose(uptime_file);
        }
    }
    // Закрытие файлового потока файла с pid'ами
    fclose(pid_file);
    return;
}

void write_pids_stat(char csv_name[]) {
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
        get_pid_stat(pid, csv_name, "yes");
        //get_pid_stat(pid, csv_name, "no");
	}
	(void)closedir(dir_stream);
    return;
}

int main(int argc, char *argv[]) {
    csv_preparation("proc_stat.csv");
    write_pids_stat("proc_stat.csv");
    printf("Генерирование csv файла со статистическими данными завершено!\n");
    return 0;
}
