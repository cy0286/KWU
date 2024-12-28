#include <stdio.h> 
#include <stddef.h> // offsetof이 정의된 헤더 파일 
struct e1
{
	int a; //4byte 
	char b[5]; //8byte 
};
struct e2
{
	struct e1 a; //12byte 
	char b; //4byte 
};
int main()
{
	printf("구조체 크기 : %d\n", sizeof(struct e1)); //struct e1의 구조체 크기 출력 
	printf("구조체 크기 : %d\n", sizeof(struct e2)); //struct e2의 구조체 크기 출력 
	printf("구조체 e1의 a의 위치 : %d\n", offsetof(struct e1, a)); //struct e1의 멤버변수 a의 위치 출력
	printf("구조체 e1의 b의 위치 : %d\n", offsetof(struct e1, b)); //struct e1의 멤버변수 b의 위치 출력
	printf("구조체 e2의 a의 위치 : %d\n", offsetof(struct e2, a)); //struct e2의 멤버변수 a의 위치 출력
	printf("구조체 e2의 b의 위치 : %d\n", offsetof(struct e2, b)); //struct e2의 멤버변수 	b의 위치 출력
	return 0;
}