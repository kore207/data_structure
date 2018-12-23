#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_CAPACITY	 3 //배열 재할당을 위해 작게 설정함.
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
	init_directory(); //이 함수에서 배열 names와 numbers를 생성한다.
	process_command(); // 사용자 명령을 받는 함수로 처리
}

void init_directory() {
	names = (char**)malloc(INIT_CAPACITY * sizeof(char *));
	numbers = (char**)malloc(INIT_CAPACITY * sizeof(char *)); //byte 수를 직접 숫자로 지정하는것보다 sizeof연산자를 사용하는게 소스적으로 바람직하다.
}

void process_command() {

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



