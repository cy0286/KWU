#include <stdio.h> 
double get_array_avg(int values[], int n);
void print_array(int values[], int n);

int main(void)
{
    int data[5] = { 10, 20, 30, 40, 50 };
    int i;
    double avg;

    print_array(data, 5);
    avg = get_array_avg(data, 5);
    printf("배열 원소들의 평균 = %f", avg); // 배열 원소의 평균 출력 
    return 0;
}

double get_array_avg(int values[], int n) // 배열 원소의 평균을 계산하는 함수 
{
    int i; // int형 변수 i 
    double sum = 0.0; // 초기화 
    for (i = 0; i < n; i++)
    {
        sum += values[i];
    }
    return sum / n;
}

void print_array(int values[], int n) // 배열 원소를 출력하는 함수 
{
    int i; // int형 변수 i 
    printf("[");
    for (i = 0; i < n; i++)
    {
        printf(" %d ", values[i]); // 배열 원소 출력 
    }
    printf("]");
    printf("\n");
    return 0;
}