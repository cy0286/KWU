#include <stdio.h> 
int main()
{
	char ch; // ĳ�������� ������ �޸� ������ ���� �� ������ �̸��� ch�� �� 
	char* p; // ������ ���� p, ������ �ּ� ���� 
	ch = 'A'; // ���� ch�� ���� A�� ���� 
	p = &ch;
	printf("ch�� ������ �ִ� ��: ch ==> %c\n", ch);
	printf("ch�� �ּ�(address):&ch ==> %d\n", &ch);
	printf("p�� ������ �ִ� �� : p ==> %d\n", p);
	printf("p�� ����Ű�� ���� ������ : *p ==> %c\n", *p);
}