#include <stdio.h> 
int main()
{
	char ch; // 캐릭터형의 데이터 메모리 공간을 만들 때 공간의 이름을 ch로 함 
	char* p; // 포인터 변수 p, 문자형 주소 저장 
	ch = 'A'; // 변수 ch에 문자 A를 넣음 
	p = &ch;
	printf("ch가 가지고 있는 값: ch ==> %c\n", ch);
	printf("ch의 주소(address):&ch ==> %d\n", &ch);
	printf("p가 가지고 있는 값 : p ==> %d\n", p);
	printf("p가 가리키는 곳의 실제값 : *p ==> %c\n", *p);
}