#include <stdio.h> 
int* sum(int a, int b); // int형 변수의 주소를 반환하는 함수 선언 
int main(void)
{
	int* resp; // 반환값을 저장할 포인터 resp 
	resp = sum(10, 20); // resp에 반환된 주소 저장 
	printf("두 정수의 합 : %d\n", *resp); // resp가 가리키는 변수의 값 출력 
	return 0;
}
int* sum(int a, int b) // int형 변수의 주소를 반환하는 함수 
{
	static int res; // 정적 지역 변수 res 선언 
	res = a + b; // a + b의 합을  res에 저장 
	return &res; // 정적 지역 변수의 주소값 반환 
}