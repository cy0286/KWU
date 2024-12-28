#include <stdio.h> 
int main()
{
	int i, * p, arr[] = { 5, 10, 15, 20, 25 }; // int형 변수 i, int형 포인터 p, int형 배열 선언, 배열은 초기화
	printf("arr[0] is %d.\n", arr[0]); // 첫번째 배열값 출력 
	printf("arr is %d.\n", *arr); // 배열의 주소에 *연산자를 이용해 배열값 출력 
	p = arr; // 포인터 변수 p가 arr을 가리킴 
	for (i = 0; i < 5; i++)
		printf("%d\t", *(p + i)); // p배열의 i번째 요소의 값을 출력 
	printf("\n");
	p = arr; // 포인터 변수 p가 arr을 가리킴 
	for (i = 0; i < 5; i++)
		printf("%d\t", *p++); // p의 주소를 한 칸 옮긴 값을 출력 
	printf("\n");
	p = arr; // 포인터 변수 p가 arr을 가리킴 
	for (i = 0; i < 5; i++)
		printf("%d\t", (*p)++); // p가 가르키고 있는 값을 증가시켜 출력 
	printf("\n");
	return 0;
}