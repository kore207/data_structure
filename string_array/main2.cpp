#include <stdio.h>
#include <ctype.h> //white space �������� �˻��ϴ� isspace �Լ��� ����

#define BUFFER_SIZE 40


int read_line_with_compression(char compressed[], int limit);

int main2(void)
{
	char buffer[BUFFER_SIZE];

	while (1)
	{
		printf("$ ");		
		int length = read_line_with_compression(buffer, BUFFER_SIZE); //�Ϻ��ϰ� �����Ҽ� �ִ� �Լ��� ����� ����ϴ°͵� ���� ����̴�.
		printf("%s: %d\n", buffer, length);
	}

	return 0;
}

int read_line_with_compression(char compressed[], int limit)
{
	int ch, i = 0;
	while ((ch = getchar()) != '\n')
	{
		if (i < limit - 1 && (ch != ' ' || i > 0 && !isspace(compressed[i - 1])))
			compressed[i++] = ch;
	}
	if (i > 0 && isspace(compressed[i - 1])) //���� ������ ���ڰ� �����ΰ�� ����ó��
		i--;
	compressed[i] = '\0';
	return i;
}