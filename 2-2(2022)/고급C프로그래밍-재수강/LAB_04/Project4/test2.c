#include <stdio.h> 
void transpose(int a[][3], int row); //행렬의 열 요소와 행 요소를 바꿔주는 함수 
void print_matrix(int a[][3], int row_size, int col_size); //행렬 출력 함수 
int main()
{
	int a[3][3] = { {13, 4, 30}, {34, 2, 5}, {7, 15, 27} }; // 배열a 선언과 동시에 초기화 
	printf("a 배열 리스트\n");
	print_matrix(a, 3, 3);
	printf("전치행열 b 배열 리스트\n");
	transpose(a, 3);
	return 0;
}

void transpose(int a[][3], int row) //행렬의 열 요소와 행 요소를 바꿔주는 함수 
{
	int b[3][3]; //전치행렬 b 
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

void print_matrix(int a[][3], int row_size, int col_size) //행렬 출력 함수 
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