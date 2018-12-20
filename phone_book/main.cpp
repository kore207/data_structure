#include <iostream>
#include <stdio.h>
#include <string.h>

#define CAPACITY 100
#define BUFFER_SIZE 100

char *names[CAPACITY];
char *numbers[CAPACITY];
int n = 0;

void add();
void find();
void status();
void remove();

int main()
{
	char command[BUFFER_SIZE];
	while (1)
	{
		printf("$ ");
		scanf("%s", command);

		if (strcmp(command, "add") == 0)
			add();
		else if (strcmp(command, "find") == 0)
			find();
		else if (strcmp(command, "status") == 0)
			status();
		else if (strcmp(command, "remove") == 0)
			remove();
		else if (strcmp(command, "exit") == 0)
			break;
	}
	return 0;
}

void add()
{
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
	scanf("%s", buf1);
	scanf("%s", buf2);

	names[n] = strdup(buf1); //strdup ->buf1의 크기에 맞게 다시 할당을 해서 복제한다 , buf1은 지역변수이기 때문에 직접 names에 넣을수 없다.(사라져 버림)
	numbers[n] = strdup(buf2);
	n++;

	printf("%s was added sucssesfuly\n", buf1);
}

void find()
{
	char buf[BUFFER_SIZE];
	scanf("%s", buf);

	int i;
	for (i = 0; i < n; i++)
	{
		if (strcmp(buf, names[i]) == 0)
		{
			printf("%s\n", numbers[i]);
			return;
		}
	}
	printf("No person named '%s' exists");
}

void status()
{
	int i;
	for (i = 0; i < n; i++)
		printf("%s   %s\n", names[i], numbers[i]);
	printf("Total %d persons.\n", n);
}

void remove()
{
	char buf[BUFFER_SIZE];
	scanf("%s", buf);
	int i;
	for (i = 0; i < n; i++)
	{
		if (strcmp(buf, names[i]) == 0)
		{
			names[i] = names[n - 1];
			numbers[i] = numbers[n - 1];
			n--;
			printf("'%s' remove successfully. \n", buf);
			return;
		}
	}
	printf("No person named '%s' exists.\n", buf);
}