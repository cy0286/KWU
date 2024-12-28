#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
void get(double, int*, double*); //정수부와 실수부로 나누는 함수 
int main()
{
	double value = 0;
	int integer; //정수
	double real; //실수 
	printf("실수를 입력하세요 : ");
	scanf("%lf", &value); //실수 입력 
	get(value, &integer, &real); //정수부와 실수부로 나누는 함수에 값 넣어줌 
	printf("정수부 : %d\n", integer);
	printf("실수부 : %f\n", real);
	return 0;
}
void get(double value, int* integer, double* real) //정수부와 실수부로 나누는 함수 
{
	*integer = (int)value;
	*real = value - *integer;
}