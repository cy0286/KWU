#include <Stdio.h> 

int main()
{
	int arr[3][7] = { {6, 12, 18, 24, 30, 0 ,0}, {36, 42, 48, 54, 60, 0, 0}, {66, 72, 78, 84,
   90, 0, 0} }; //�迭 ����� �ʱ�ȭ 
	int i, j; //i=row, j=col 
	int sum; //���� �� 
	int avg; //���� ��� 

	for (i = 0; i < 3; i++)
	{
		sum = (arr[i][0] + arr[i][1] + arr[i][2] + arr[i][3] + arr[i][4]); //�� ���� �� 
		avg = sum / 5; //�� ���� ��� 

		for (j = 0; j < 5; j++)
		{
			printf("  %2d ", arr[i][j]); //6�� ��� ��� 
		}

		printf(" -> %d", i);

		for (j = 5; j < 6; j++) //5���� �� ���� �� ��� 
		{
			sum += arr[i][j];
			printf(" ���� �� : %d,", sum);
		}

		for (j = 6; j < 7; j++) //6���� �� ���� ��� ��� 
		{
		}
		printf(" ��� : %d", avg);
		printf("\n");
	}
	return 0;
}