#include <stdio.h> 
int* sum(int a, int b); // int�� ������ �ּҸ� ��ȯ�ϴ� �Լ� ���� 
int main(void)
{
	int* resp; // ��ȯ���� ������ ������ resp 
	resp = sum(10, 20); // resp�� ��ȯ�� �ּ� ���� 
	printf("�� ������ �� : %d\n", *resp); // resp�� ����Ű�� ������ �� ��� 
	return 0;
}
int* sum(int a, int b) // int�� ������ �ּҸ� ��ȯ�ϴ� �Լ� 
{
	static int res; // ���� ���� ���� res ���� 
	res = a + b; // a + b�� ����  res�� ���� 
	return &res; // ���� ���� ������ �ּҰ� ��ȯ 
}