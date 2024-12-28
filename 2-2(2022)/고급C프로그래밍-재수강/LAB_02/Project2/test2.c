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
    printf("�迭 ���ҵ��� ��� = %f", avg); // �迭 ������ ��� ��� 
    return 0;
}

double get_array_avg(int values[], int n) // �迭 ������ ����� ����ϴ� �Լ� 
{
    int i; // int�� ���� i 
    double sum = 0.0; // �ʱ�ȭ 
    for (i = 0; i < n; i++)
    {
        sum += values[i];
    }
    return sum / n;
}

void print_array(int values[], int n) // �迭 ���Ҹ� ����ϴ� �Լ� 
{
    int i; // int�� ���� i 
    printf("[");
    for (i = 0; i < n; i++)
    {
        printf(" %d ", values[i]); // �迭 ���� ��� 
    }
    printf("]");
    printf("\n");
    return 0;
}