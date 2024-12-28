#include <Stdio.h> 

int main()
{
	int arr[3][7] = { {6, 12, 18, 24, 30, 0 ,0}, {36, 42, 48, 54, 60, 0, 0}, {66, 72, 78, 84,
   90, 0, 0} }; //배열 선언과 초기화 
	int i, j; //i=row, j=col 
	int sum; //행의 합 
	int avg; //행의 평균 

	for (i = 0; i < 3; i++)
	{
		sum = (arr[i][0] + arr[i][1] + arr[i][2] + arr[i][3] + arr[i][4]); //각 행의 합 
		avg = sum / 5; //각 행의 평균 

		for (j = 0; j < 5; j++)
		{
			printf("  %2d ", arr[i][j]); //6의 배수 출력 
		}

		printf(" -> %d", i);

		for (j = 5; j < 6; j++) //5열에 각 행의 합 출력 
		{
			sum += arr[i][j];
			printf(" 행의 합 : %d,", sum);
		}

		for (j = 6; j < 7; j++) //6열에 각 행의 평균 출력 
		{
		}
		printf(" 평균 : %d", avg);
		printf("\n");
	}
	return 0;
}