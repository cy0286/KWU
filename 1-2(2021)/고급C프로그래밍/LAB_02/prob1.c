#include <stdio.h>
#define MAX_STD 3 // ����ü �迭�� ũ��

struct student {
    int number;
    int korean, english, math;
    double average;
}std[MAX_STD]; // ����ü �迭�� ����

int main()
{
    printf("==================================================== \n");
    printf("�й� : 2021202058 \n");
    printf("�̸� : ��ä�� \n");
    printf("==================================================== \n");

    int i;
    double total_average = 0;

    for (int i = 0; i < MAX_STD; i++) {
        printf("%d��° �л��� �й��� �Է��ϼ��� : ", i + 1); // ����ü �迭�� �Է�
        scanf_s("%d", &(std[i].number));
        printf("%d��° �л��� ���� ������ �Է��ϼ��� : ", i + 1);
        scanf_s("%d", &(std[i].korean));
        printf("%d��° �л��� ���� ������ �Է��ϼ��� : ", i + 1);
        scanf_s("%d", &(std[i].english));
        printf("%d��° �л��� ���� ������ �Է��ϼ��� : ", i + 1);
        scanf_s("%d", &(std[i].math));
        std[i].average = (double)(std[i].korean + std[i].english + std[i].math) / 3; // �� �л��� ��� ���ϱ�
        printf("\n");
    }

    for (int i = 0; i < MAX_STD; i++)
    {
        printf("%d��° �л��� ����� %f �Դϴ�. \n", i + 1, std[i].average);
    }
    return 0;
}
