#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

#define BUFFER_SIZE 40

int read_line(char str[], int limit);

int main(void)
{
	cout << "자료구조 문자열 예제";
	char buffer[BUFFER_SIZE];

	while (1)
	{
		printf("$ ");
		//scanf("%s", buffer); //공백을 기준으로 읽어 들임
		//gets(buffer); //메모리를 침범하기 때문에 사용하지 않는게 좋다
		//fgets(buffer, BUFFER_SIZE, stdin); //gets 와 달리 사이즈가 주어지기 때문에 안정정이다 stdin 은 키보드 입력이라고 보면됌
		//줄이 바뀌는 이유는 마지막에 엔터를 입력할떄까지 읽다가 줄바꿈문자인 엔터를 인식하기 때문에 줄이 바뀐다.
		//buffer[strlen(buffer) - 1] = '\0'; //이걸로 줄 안바뀌게 할 수 있음
		read_line(buffer, BUFFER_SIZE); //완벽하게 통제할수 있는 함수를 만들어 사용하는것도 좋은 방법이다.
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