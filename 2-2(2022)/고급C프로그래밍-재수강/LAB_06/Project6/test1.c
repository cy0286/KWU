#include <stdio.h> 
#include <stddef.h> // offsetof�� ���ǵ� ��� ���� 
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
	printf("����ü ũ�� : %d\n", sizeof(struct e1)); //struct e1�� ����ü ũ�� ��� 
	printf("����ü ũ�� : %d\n", sizeof(struct e2)); //struct e2�� ����ü ũ�� ��� 
	printf("����ü e1�� a�� ��ġ : %d\n", offsetof(struct e1, a)); //struct e1�� ������� a�� ��ġ ���
	printf("����ü e1�� b�� ��ġ : %d\n", offsetof(struct e1, b)); //struct e1�� ������� b�� ��ġ ���
	printf("����ü e2�� a�� ��ġ : %d\n", offsetof(struct e2, a)); //struct e2�� ������� a�� ��ġ ���
	printf("����ü e2�� b�� ��ġ : %d\n", offsetof(struct e2, b)); //struct e2�� ������� 	b�� ��ġ ���
	return 0;
}