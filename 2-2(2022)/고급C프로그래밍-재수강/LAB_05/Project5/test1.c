#include <stdio.h> 
max_ptr(int m[], int size, int** pmax); //배열의 큰값을 가르키게 하는 함수 
int main()
{
	int m[5] = { 10, 20, 30, 40, 50 }; //배열에 임의의 초기값을 줌 
	int* pmax; //가장 큰 수를 가르킬 포인터 변수 pmax 선언 
	max_ptr(m, 5, &pmax); //pmax의 주소 &pmax는 이중포인터 
	printf("가장 큰 값은 %d", *pmax); //가장 큰 값 출력 
	return 0;
}
max_ptr(int m[], int size, int** pmax) //배열의 큰값을 가르키게 하는 함수 
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