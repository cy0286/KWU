#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> 
double get_array_avg(int* values, int n);
void print_array(int* values, int n);
max_ptr(int m[], int size, int** pmax);

int main(void)
{
    int value = 0;
    printf("배열의 크기를 입력하시오 : "); //배열의 크기 입력 받음 
    scanf("%d", &value);
    int* data = malloc(sizeof(int) * value); //동적할당으로 배열 입력 받음 
    double avg;
    printf("배열 입력하기(");
    printf("%d", value);
    printf("개)\n");

    for (int i = 0; i < value; i++) //배열 입력 
    {
        scanf("%d", &data[i]);
    }

    print_array(data, value); //배열 출력 

    int* pmax;
    max_ptr(data, value, &pmax);
    printf("가장 큰 값은 %d\n", *pmax); //배열의 가장 큰 값 출력 

    avg = get_array_avg(data, value);
    printf("배열 원소들의 평균 = %f\n", avg); // 배열 원소의 평균 출력 

    return 0;
}

double get_array_avg(int* values, int n) // 배열 원소의 평균을 계산하는 함수 
{
    int i;
    double sum = 0.0;
    for (i = 0; i < n; i++)
    {
        sum += values[i];
    }
    return sum / n;
}

void print_array(int* values, int n) // 배열 원소를 출력하는 함수 
{
    int i;
    printf("[");
    for (i = 0; i < n; i++)
    {
        printf(" %d ", values[i]); // 배열 원소 출력 
    }
    printf("]");
    printf("\n");
}

max_ptr(int m[], int size, int** pmax) //배열의 큰값을 가르키게 하는 함수 
{
    int value = 0;
    int max;
    max = m[0];
    for (int i = 0; i < size; i++)
    {
        if (max < m[i])
        {
            max = m[i];
            *pmax = &m[i];
        }
    }
}