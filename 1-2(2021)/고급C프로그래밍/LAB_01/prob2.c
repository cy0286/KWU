#include<stdio.h>
int main()
{
    printf("==================================================== \n");
    printf("�й� : 2021202058 \n");
    printf("�̸� : ��ä�� \n");
    printf("==================================================== \n");

    int array[8] = { 1, 2, 3, 4, 5, 6, 7, 8 }; 
    printf("array �迭 �� : 1 2 3 4 5 6 7 8 \n");
    printf("shift �� array �迭 �� : ");
    printf("%d, %d, %d, %d, %d, %d, %d, %d \n",  array[7], array[0], array[1], array[2], array[3], array[4], array[5], array[6]); // �迭���
    return 0;
}