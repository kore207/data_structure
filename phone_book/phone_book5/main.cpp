#include <stdio.h>
#include <string.h>
#include <stdlib.h>

 //call-by-value or pass-by-assignment
//�������� ȣ�� ->ȣ��ÿ� ��� ������� �����(C��� �Ű����� ������ �⺻ ���)
//����ü������ ����Ǵ� ���� ���� ����.
//Ư�� return �������� ���������� �ι� ���� �Ǵ� ������ �ִ�. 

#define INIT_CAPACITY 100
#define BUFFER_LENGTH 100

typedef struct {
	char *name;
	char *number;
	char *email;
	char *group;
}Person;

Person **directory;
int capacity;
int n;

void init();
int read_line(FILE *fp, char str[], int n);
void load(char *fileName);
void add(char *name, char *number, char *email, char *group);
void reallocate();

void init() {
	directory = (Person **)malloc(INIT_CAPACITY * sizeof(Person *));
	capacity = INIT_CAPACITY;
	n = 0;
}

void remove(char *name) {
	//������ �ٸ���
	//release_person �� �Լ��� ���� free ��������Ѵ�.
	//ex free(p->name);
	//if(p->number != NULL) free(p->numver);
	//---
	//free(p);
}

void reallocate() {
	capacity *= 2;
	Person **tmp = (Person **)malloc(capacity * sizeof(Person *));
	for (int i = 0; i < n; i++)
		tmp[i] = directory[i];
	free(directory);
	directory = tmp;
}

void add(char *name, char *number, char *email, char *group)
{
	if (n >= capacity)
		reallocate();

	int i = n - 1;
	while (i >= 0 && strcmp(directory[i]->name, name) > 0) {
		directory[i + 1] = directory[i]; //ver.4 �ʹ� �ٸ��� ������ �� �ּҸ� ����Ǵ°��̴�.
		i--;
	}
	//������ -> �� -> �뷮���� -> free
	directory[i + 1] = (Person *)malloc(sizeof(Person)); //���� ���⼭ �ٽ� ����ü�� �޸𸮸� �Ҵ� ����� �Ѵ�.

	directory[i + 1]->name = name;
	directory[i + 1]->number = number;
	directory[i + 1]->email = email;
	directory[i + 1]->group = group;

	n++;
}

void load(char *fileName) {
	char buffer[BUFFER_LENGTH];
	char *name, *number, *email, *group;
	char *token;

	FILE *fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	while (1) {
		if (read_line(fp, buffer, BUFFER_LENGTH) <= 0)
			break;
		name = strtok(buffer, "#");

		token = strtok(NULL, "#");
		if (strcmp(token, " ") == 0)
			number = NULL;
		else
			number = strdup(token);

		token = strtok(NULL, "#");
		if (strcmp(token, " ") == 0)
			email = NULL;
		else
			email = strdup(email);

		token = strtok(NULL, "#");
		if (strcmp(token, " ") == 0)
			group = NULL;
		else
			group = strdup(group);
		add(strdup(name), number, email, group);
	}
	fclose(fp);
}

int read_line(FILE *fp, char str[], int n)
{
	int ch, i = 0;

	while (ch = fgetc(fp) != '\n' && ch != EOF)
		if (i < n)
			str[i++] = ch;
	str[i] = '\0';
}



int main() {
	char command_line[BUFFER_LENGTH];
	char *command, *argument;
	char name_str[BUFFER_LENGTH];


}