#include <stdio.h> 
max_ptr(int m[], int size, int** pmax); //�迭�� ū���� ����Ű�� �ϴ� �Լ� 
int main()
{
	int m[5] = { 10, 20, 30, 40, 50 }; //�迭�� ������ �ʱⰪ�� �� 
	int* pmax; //���� ū ���� ����ų ������ ���� pmax ���� 
	max_ptr(m, 5, &pmax); //pmax�� �ּ� &pmax�� ���������� 
	printf("���� ū ���� %d", *pmax); //���� ū �� ��� 
	return 0;
}
max_ptr(int m[], int size, int** pmax) //�迭�� ū���� ����Ű�� �ϴ� �Լ� 
{
	int max;
	max = m[0];
	for (size = 0; size < 5; size++)
	{
		if (max < m[size])
		{
			max = m[size];
			*pmax = &m[size];
		}
	}
}