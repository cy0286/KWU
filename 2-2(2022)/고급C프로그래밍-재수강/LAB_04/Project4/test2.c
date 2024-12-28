#include <stdio.h> 
void transpose(int a[][3], int row); //����� �� ��ҿ� �� ��Ҹ� �ٲ��ִ� �Լ� 
void print_matrix(int a[][3], int row_size, int col_size); //��� ��� �Լ� 
int main()
{
	int a[3][3] = { {13, 4, 30}, {34, 2, 5}, {7, 15, 27} }; // �迭a ����� ���ÿ� �ʱ�ȭ 
	printf("a �迭 ����Ʈ\n");
	print_matrix(a, 3, 3);
	printf("��ġ�࿭ b �迭 ����Ʈ\n");
	transpose(a, 3);
	return 0;
}

void transpose(int a[][3], int row) //����� �� ��ҿ� �� ��Ҹ� �ٲ��ִ� �Լ� 
{
	int b[3][3]; //��ġ��� b 
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			b[j][i] = a[i][j];
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			a[i][j] = b[i][j];
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("  %2d  ", a[i][j]);
		}
		printf("\n");
	}
}

void print_matrix(int a[][3], int row_size, int col_size) //��� ��� �Լ� 
{
	int i, j;
	for (i = 0; i < row_size; i++)
	{
		for (j = 0; j < col_size; j++)
		{
			printf("  %2d  ", a[i][j]);
		}
		printf("\n");
	}
}