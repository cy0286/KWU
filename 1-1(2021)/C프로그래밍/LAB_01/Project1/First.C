#include <stdio.h>

int main()
{
	int data; // 정수형 변수를 선언한다.

	printf("경수를 입력하세요==>");
	scanf_s("%d", &data); // 키보드로 경수를 입력 받는다.
	
	printf("10진수=> %d\n", data); // 10진수(%), 16진수(X), 8진수()를 출력한다.
	printf("16진수==> %X\n", data);
	printf("8진수 ==> %o\n", data);
}