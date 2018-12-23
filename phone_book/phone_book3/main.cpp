#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_CAPACITY	 3 //�迭 ���Ҵ��� ���� �۰� ������.
#define BUFFER_SIZE		50

char ** names; 
char ** numbers;

int capacity = INIT_CAPACITY;
int n = 0;

char delim[] = " ";

void init_directory();
void process_command();

int main()
{
	init_directory(); //�� �Լ����� �迭 names�� numbers�� �����Ѵ�.
	process_command(); // ����� ����� �޴� �Լ��� ó��
}

void init_directory() {
	names = (char**)malloc(INIT_CAPACITY * sizeof(char *));
	numbers = (char**)malloc(INIT_CAPACITY * sizeof(char *)); //byte ���� ���� ���ڷ� �����ϴ°ͺ��� sizeof�����ڸ� ����ϴ°� �ҽ������� �ٶ����ϴ�.
}

void process_command() {

}

int read_line(char str[], int limit)//line ���� �Է��� fgets, getline ���� �Լ��鵵 �ִ�.
{
	int ch, i = 0;

	while ((ch = getchar()) != '\n')
		if (i < limit - 1)
			str[i++] = ch;

	str[i] = '\0';

	return i;	
}



