#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

#define BUFFER_SIZE 40

int read_line(char str[], int limit);

int main(void)
{
	cout << "�ڷᱸ�� ���ڿ� ����";
	char buffer[BUFFER_SIZE];

	while (1)
	{
		printf("$ ");
		//scanf("%s", buffer); //������ �������� �о� ����
		//gets(buffer); //�޸𸮸� ħ���ϱ� ������ ������� �ʴ°� ����
		//fgets(buffer, BUFFER_SIZE, stdin); //gets �� �޸� ����� �־����� ������ �������̴� stdin �� Ű���� �Է��̶�� �����
		//���� �ٲ�� ������ �������� ���͸� �Է��ҋ����� �дٰ� �ٹٲ޹����� ���͸� �ν��ϱ� ������ ���� �ٲ��.
		//buffer[strlen(buffer) - 1] = '\0'; //�̰ɷ� �� �ȹٲ�� �� �� ����
		read_line(buffer, BUFFER_SIZE); //�Ϻ��ϰ� �����Ҽ� �ִ� �Լ��� ����� ����ϴ°͵� ���� ����̴�.
		printf("%s: %d\n", buffer, strlen(buffer));
	}

	return 0;
}

int read_line(char str[], int limit)
{
	int ch, i = 0;

	while ((ch = getchar()) != '\n')
		if (i < limit)
			str[i++] = ch;

	str[i] = '\0';
	return i;
}