#include<stdio.h>

void reverse(int*, int);

int main()
{
    printf("==================================================== \n");
    printf("�й� : 2021202058 \n");
    printf("�̸� : ��ä�� \n");
    printf("==================================================== \n");

    int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; // ���̰� 10�� int�� ���� ���� �� �ʱ�ȭ
    int i;
    printf("�ʱ� �迭 �� : ");
    for(int i = 0; i < 10; i++) {
        printf(" %d", arr[i]);
    }
    printf("\n");
    reverse(arr, 10);
    return 0;
}

void reverse(int* A, int size) {
    int i;
    printf("��ȯ �� �迭 �� : ");
    for (i = size - 1; i >= 0; i--) {
        printf("%d ", A[i]); // �������� ���
    }
    printf("\n");
}
