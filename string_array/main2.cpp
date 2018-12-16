#include <stdio.h>
#include <ctype.h> //white space 문자인지 검사하는 isspace 함수를 제공

#define BUFFER_SIZE 40


int read_line_with_compression(char compressed[], int limit);

int main2(void)
{
	char buffer[BUFFER_SIZE];

	while (1)
	{
		printf("$ ");		
		int length = read_line_with_compression(buffer, BUFFER_SIZE); //완벽하게 통제할수 있는 함수를 만들어 사용하는것도 좋은 방법이다.
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
	if (i > 0 && isspace(compressed[i - 1])) //실제 마지막 문자가 공백인경우 예외처리
		i--;
	compressed[i] = '\0';
	return i;
}