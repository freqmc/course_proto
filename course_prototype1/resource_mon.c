#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <conio.h>

typedef struct {
	int cpu_load;
	int ram_use;
	int storage_use;
} InputValues;

typedef struct {
	int cpu_load;
	int ram_use;
	int storage_use;
} AlertValues;

int CheckValues(InputValues, AlertValues);
char *AlertMessages(int);
void CreateLogFile(InputValues);

int main() {
	AlertValues alert_values = {
		.cpu_load = 60, .ram_use = 70, .storage_use = 40
	};
	InputValues user_value = {
	.cpu_load = 0, .ram_use = 0, .storage_use = 0
	};
	int Errors;

	setlocale(LC_CTYPE, "RUS");
	
	while (1) {
		printf("Введите процент загруженности процессора: ");
		scanf("%d", &user_value.cpu_load);
		getchar();
		if (user_value.cpu_load < 0 || user_value.cpu_load > 100) {
			printf("Некорректный диапазон значений! Введите значения от 0 до 100.\n");
			printf("\n");
			continue;
		}

		printf("Введите процент загруженности оперативной памяти: ");
		scanf("%d", &user_value.ram_use);
		getchar();
		if (user_value.ram_use < 0 || user_value.ram_use > 100) {
			printf("Некорректный диапазон значений! Введите значения от 0 до 100.\n");
			printf("\n");
			continue;
		}
		
		printf("Введите процент загруженности дискового пространства: ");
		scanf("%d", &user_value.storage_use);
		getchar();
		if (user_value.storage_use < 0 || user_value.storage_use > 100) {
			printf("Некорректный диапазон значений! Введите значения от 0 до 100.\n");
			printf("\n");
			continue;
		}
		
		Errors = CheckValues(user_value, alert_values);
		char *Alert = AlertMessages(Errors);
		
		CreateLogFile(user_value);

		printf("Загрузка процессора: %d%%\n", user_value.cpu_load);
		printf("Загрузка оперативной памяти: %d%%\n", user_value.ram_use);
		printf("Загрузка дискового пространства: %d%%\n", user_value.storage_use);
		printf("%s\n", Alert);
		
		printf("Продолжить? Да - [y] Нет - [n]\n");
		char StopButton = getch();
		if (StopButton == 'n') {
			break;
		} else if (StopButton == 'y') {
			printf("\n");
		}
	}
	return 0;
}

int CheckValues(InputValues UserValues, AlertValues WarnValues) {
	int ErrorCounter = 0;
	if (UserValues.cpu_load > WarnValues.cpu_load) {
		ErrorCounter++;
	}
	if (UserValues.ram_use > WarnValues.ram_use) {
		ErrorCounter++;
	}
	if (UserValues.storage_use > WarnValues.storage_use) {
		ErrorCounter++;
	}
	return ErrorCounter;
}

char *AlertMessages(int ErrorCounter) {
	switch (ErrorCounter) {
	case 1:
		return "Низкий уровень угрозы";
	case 2:
		return "Средний уровень угрозы";
	case 3:
		return "Высокий уровень угрозы";
	default:
		return "Показатели в норме";
	}
}

void CreateLogFile(InputValues user_values) {
	FILE* LogFile = fopen("monitor_log.txt", "a");
	
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	char timestamp[1024];
	strftime(timestamp, 1024, "%d-%m-%Y %H:%M:%S", t);
	
	fprintf(LogFile, "[%s] Загрузка процессора = %d%%, Загрузка оперативной памяти = %d%%, Загрузка дискового пространства = %d%%\n", timestamp, user_values.cpu_load, user_values.ram_use, user_values.storage_use);
	fclose(LogFile);
}