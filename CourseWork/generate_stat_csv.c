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

void get_cpu_stat(int *total_jiffies, int *work_jiffies) {
    FILE *proc_stat_file;
    char buffer[128];
    int count = 0;
    int user, nice, system, idle, iowait, irq, softirq;

    proc_stat_file = fopen("/proc/stat", "r");
    if (proc_stat_file == NULL) {
        // В случае ошибки - досрочный выход из функции
        return;
    }

    while ((fscanf(proc_stat_file, "%s", buffer) == 1) && (count < 8) ) {
        if (count == 1) sscanf(buffer, "%d", &user);
        if (count == 2) sscanf(buffer, "%d", &nice);
        if (count == 3) sscanf(buffer, "%d", &system);
        if (count == 4) sscanf(buffer, "%d", &idle);
        if (count == 5) sscanf(buffer, "%d", &iowait);
        if (count == 6) sscanf(buffer, "%d", &irq);
        if (count == 7) sscanf(buffer, "%d", &softirq);
        count++;
    }
    *total_jiffies = user+nice+system+idle+iowait+irq+softirq;
    *work_jiffies = user+nice+system;

    fclose(proc_stat_file);
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
            }
            while ((fscanf(pid_file, "%s", buffer) == 1) && (count < 25) ) {
                if (count == 13) {
                    sscanf(buffer, "%d", &PROCESS_UTIME);
                }
                if (count == 14) {
                    sscanf(buffer, "%d", &PROCESS_STIME);
                }
                if (count == 21) {
                    sscanf(buffer, "%d", &PROCESS_STARTTIME);
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
            printf("%8d %10d %8d %10d %7d%c\n", pid_number, PROCESS_UTIME_SEC,PROCESS_STIME_SEC, PROCESS_ELAPSED_SEC, PROCESS_USAGE, 37);
            fclose(uptime_file);
        }
    }
    // Закрытие файлового потока файла с pid'ами
    fclose(pid_file);
    return;
}

void write_pids_stat(char csv_name[], char cpu_stat[], int print_count) {
    DIR * dir_stream = NULL;
	struct dirent * procfs_entry = NULL;
	dir_stream = opendir(LINUX_PROC_TASK_PATH);
	pid_t pid;
    int count = 0;

	if(dir_stream == NULL) {
		perror("opendir");
	}

	while((procfs_entry = readdir(dir_stream)) != NULL) {
        if (print_count == -1 && count == 23) {
            break;
        }
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
        get_pid_stat(pid, csv_name, cpu_stat);
        count++;

	}
	(void)closedir(dir_stream);
    return;
}

void print_cpu_stat(int seconds) {
    int total_jiffies_1, work_jiffies_1;
    int total_jiffies_2, work_jiffies_2;
    int work_over_period, total_over_period;
    double cpu_util;

    get_cpu_stat(&total_jiffies_1, &work_jiffies_1);
    sleep(seconds);
    get_cpu_stat(&total_jiffies_2, &work_jiffies_2);

    work_over_period = work_jiffies_2 - work_jiffies_1;
    total_over_period = total_jiffies_2 - total_jiffies_1;
    cpu_util = work_over_period / total_over_period * 100;

    write_pids_stat("proc_stat.csv", "yes", 0);
    printf("%8s %10s %8s %10s %8s\n", "PID", "USER_SEC", "KERN_SEC", "CPU_TIME", "%CPU");
    printf("\nCPU UTILIZATION: %5lf%c\n", cpu_util, 37);
}

int main(int argc, char *argv[]) {
    csv_preparation("proc_stat.csv");
    write_pids_stat("proc_stat.csv", "no", 0);
    printf("Генерирование csv файла со статистическими данными завершено!\n");
    while (42) {
        print_cpu_stat(1);
    }
    return 0;
}
