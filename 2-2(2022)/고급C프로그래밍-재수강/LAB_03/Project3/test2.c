#include <stdio.h> 

int main()
{
	int a[6] = { 5, 10, 15, 20, 25, 30 }; // 배열 선언과 동시에 초기화 
	int* p = a;

	p = a;
	for (int i = 0; i < 5; i++)
	{
		printf(" %d ", *p++); // p가 가르키는 값을 a에 대입후 p 증가 (주소 증가) 
	}
	printf("\n");

	p = a;
	for (int i = 0; i < 5; i++)
	{
		printf(" %d ", (*p)++); // p가 가르키는 값을 a에 대입후 p가 가르키는 값 i를 증가(값 증가)
	}
	printf("\n");

	p = a;
	for (int i = 0; i < 5; i++)
	{
		printf(" %d ", *++p); // p를 증가시킨 후에 p가 가르키는 값을 a에 대입 (주소 증가)
	}
	printf("\n");

	p = a;
	for (int i = 0; i < 5; i++)
	{
		printf(" %d ", *++p); // p를 증가시킨 후에 p가 가르키는 값을 a에 대입 (주소 증가)
	}
	printf("\n");
	p = a;
	for (int i = 0; i < 5; i++)
	{
		printf(" %d ", ++ * p); // p가 가르키는 값을 가져오고 그 값을 증가해 a에 대입 (값 증가)
	}
	printf("\n");
	return 0;
}