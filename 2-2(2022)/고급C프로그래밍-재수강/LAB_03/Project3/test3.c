#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
void format_display(char money[]);

int main()
{
	char money[100]; // 문자열 저장
	printf("단위를 뺀 금액 입력하고 Enter > ");
	scanf("%s", money);
	format_display(money);
	return 0;
}

void format_display(char money[]) // 문자열로 숫자를 입력 받아 천 단위 단위 표시 출력 함수 
{
	int i, len;
	const char* str = money; // 길이를 구할 문자열
	len = strlen(str);
	for (i = 0; i < strlen(str); i++) // 3자리 마다 콤마 출력
	{
		printf("%c", money[i]);
		len--; // 3자리 단위로 출력하기 위한 논리
		if (len % 3 == 0 && len != 0) // 콤마 추가
		{
			printf(",");
		}
	}
	return 0;
}
