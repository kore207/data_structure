#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#define INIT_CAPACITY	 3 //배열 재할당을 위해 작게 설정함.
#define BUFFER_SIZE		50

char ** names; 
char ** numbers;

int capacity = INIT_CAPACITY;
int n = 0;

char delim[] = " "; 

void init_directory();
void process_command();
void load(char *fileName);
void add(char * name, char* number);
int search(char*name);
int read_line(char str[], int limit);
void find(char *name);
void status();
void remove(char * name);
void save(char *fileName);
void reallocate();

int main()
{
	init_directory(); //이 함수에서 배열 names와 numbers를 생성한다.
	process_command(); // 사용자 명령을 받는 함수로 처리
}

void init_directory() {
	names = (char**)malloc(INIT_CAPACITY * sizeof(char *));
	numbers = (char**)malloc(INIT_CAPACITY * sizeof(char *)); //byte 수를 직접 숫자로 지정하는것보다 sizeof연산자를 사용하는게 소스적으로 바람직하다.
}

void process_command() {
	char command_line[BUFFER_SIZE];
	char *command, *argument1, *argument2;

	while (1) {
		printf("$ ");

		if (read_line(command_line, BUFFER_SIZE) <= 0) //아무 명령어도 없는 경우
			continue;

		command = strtok(command_line, delim);
		if (command == NULL) continue; //안전장치

		if (strcmp(command, "read") == 0) {
			argument1 = strtok(NULL, delim);

			if (argument1 == NULL) {
				printf("FILE NAME Required. \n");
				continue;
			}

			load(argument1);
		}
		else if (strcmp(command, "add") == 0) {
			argument1 = strtok(NULL, delim);
			argument2 = strtok(NULL, delim);

			if (argument1 == NULL || argument2 == NULL) {
				printf("Invalid arguments. \n");
				continue;
			}
			add(argument1, argument2);

			printf("%s was add successfully\n", argument1);
		}
		else if (strcmp(command, "find") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("Invalid arguments. \n");
				continue;
			}
			find(argument1);
		}
		else if (strcmp(command, "status") == 0)
			status();
		else if (strcmp(command, "delete") == 0) {
			argument1 = strtok(NULL, delim);
			if (argument1 == NULL) {
				printf("Invalid arguments. \n");
				continue;
			}
			remove(argument1);
		}
		else if (strcmp(command, "save") == 0) {
			argument1 = strtok(NULL, delim);
			argument2 = strtok(NULL, delim);

			if (argument1 == NULL || strcmp("as", argument1) != 0 || argument2 == NULL) {
				printf(" Invalid command format. \n");
				continue;
			}

			save(argument2);
		}
		else if (strcmp(command, "exit") == 0)
			break;
	}
}

void save(char *fileName) {
	int i; 
	FILE *fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("Open failed. \n");
		return;

	}

	for (i = 0; i < n; i++) {
		fprintf(fp, "%s %s\n", names[i], numbers[i]);
	}
	fclose(fp);
}

void status() {
	int i;
	for (i = 0; i < n; i++)
		printf("%s %s\n", names[i], numbers[i]);
	printf("Total %d persons. \n", n);
}

void find(char *name){
	int index = search(name);
	if (index == -1)
		printf("No person named '%s' exists.\n", name);
	else
		printf("%s\n", numbers[index]);
}

void remove(char * name) {
	int i = search(name);
	if (i == -1) {
		printf("No person named '%s' exists. \n", name);
		return;
	}
	int j = i;
	for (; j < n - 1; j++) {
		names[j] = names[j + 1];
		numbers[j] = numbers[j + 1];
	}
	n--;
	printf(" '%s' was deleted successfully. \n", name);
}
int search(char*name) {
	int i;
	for (i = 0; i < n; i++) {
		if (strcmp(name, names[i]) == 0) {
			return i;
		}
	}
	return -1;
}

void load(char *fileName)
{
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];

	FILE *fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	while ((fscanf(fp, "%s", buf1) != EOF)) {
		fscanf(fp, "%s", buf2);
		add(buf1, buf2);
	}
	fclose(fp);
}

void add(char * name, char* number) {
	if (n >= capacity)
		reallocate();	

	int i = n - 1;
	while (i >= 0 && strcmp(names[i], name) > 0) {
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}

	names[i + 1] = strdup(name); //name 은 호출되는곳에서 지역변수이기 때문에 복제해야한다.
	numbers[i + 1] = strdup(number);
	n++;
}

void reallocate()
{
	int i;

	capacity *= 2; //2배 
	char **tmp1 = (char **)malloc(capacity * sizeof(char *));
	char **tmp2 = (char **)malloc(capacity * sizeof(char *));

	for (i = 0; i < n; i++) {
		tmp1[i] = names[i];
		tmp2[i] = numbers[i];
	}

	free(names);
	free(numbers);

	names = tmp1;
	numbers = tmp2;
}

int read_line(char str[], int limit)//line 단위 입력은 fgets, getline 등의 함수들도 있다.
{
	int ch, i = 0;

	while ((ch = getchar()) != '\n')
		if (i < limit - 1)
			str[i++] = ch;

	str[i] = '\0';

	return i;	
}



