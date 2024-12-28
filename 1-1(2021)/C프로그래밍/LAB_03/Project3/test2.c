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
        printf("숫자 입력:");
        scanf("%d", &n);
        printf("현재까지의 최소 값은:%d\n", current_min(n));
    } while (n >= 0);
}