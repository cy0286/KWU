#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> 
double get_array_avg(int* values, int n);
void print_array(int* values, int n);
max_ptr(int m[], int size, int** pmax);

int main(void)
{
    int value = 0;
    printf("�迭�� ũ�⸦ �Է��Ͻÿ� : "); //�迭�� ũ�� �Է� ���� 
    scanf("%d", &value);
    int* data = malloc(sizeof(int) * value); //�����Ҵ����� �迭 �Է� ���� 
    double avg;
    printf("�迭 �Է��ϱ�(");
    printf("%d", value);
    printf("��)\n");

    for (int i = 0; i < value; i++) //�迭 �Է� 
    {
        scanf("%d", &data[i]);
    }

    print_array(data, value); //�迭 ��� 

    int* pmax;
    max_ptr(data, value, &pmax);
    printf("���� ū ���� %d\n", *pmax); //�迭�� ���� ū �� ��� 

    avg = get_array_avg(data, value);
    printf("�迭 ���ҵ��� ��� = %f\n", avg); // �迭 ������ ��� ��� 

    return 0;
}

double get_array_avg(int* values, int n) // �迭 ������ ����� ����ϴ� �Լ� 
{
    int i;
    double sum = 0.0;
    for (i = 0; i < n; i++)
    {
        sum += values[i];
    }
    return sum / n;
}

void print_array(int* values, int n) // �迭 ���Ҹ� ����ϴ� �Լ� 
{
    int i;
    printf("[");
    for (i = 0; i < n; i++)
    {
        printf(" %d ", values[i]); // �迭 ���� ��� 
    }
    printf("]");
    printf("\n");
}

max_ptr(int m[], int size, int** pmax) //�迭�� ū���� ����Ű�� �ϴ� �Լ� 
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