#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 

int current_min(int n)
{
    int min;
    int a;

    if (n < 100)  a = n;
    else a = 100;

    if (n <= a) min = n;
    else min = a;

    return min;
}

int main(void)
{
    int n;
    int min;

    do
    {
        printf("���� �Է�:");
        scanf("%d", &n);
        printf("��������� �ּ� ����:%d\n", current_min(n));
    } while (n >= 0);
}