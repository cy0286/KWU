#include <stdio.h>  
int main()
{
	int a, b, tmp; // 정수형 변수 3개와 포인터 변수 2개를 선언한다. 
	int* p1, * p2;
	printf("a 값 입력 : "); // a와 b에 값을 입력한다. 
	scanf_s("%d", &a);
	printf("b 값 입력 : ");
	scanf_s("%d", &b);
	p1 = &a; // 변수 a의 주솟값을 p1에 대입한다. 
	p2 = &b; // 변수 b의 주솟값을 p2에 대입한다. 
	tmp = *p1; // p1이 가리키는 곳의 실제 값을 tmp에 넣는다. 
	*p1 = *p2; // p2가 가리키는 곳의 실제 값을 p1이 가리키는 곳에 넣는다. 
	*p2 = tmp; // tmp에 저장된 값을 p2가 가리키는 곳에 넣는다. 
	printf("바뀐 값 a는 %d, b는 %d \n", a, b);
}