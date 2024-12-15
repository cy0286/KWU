#include <stdio.h>
#define MAX_STD 3 // 구조체 배열의 크기

struct student {
    int number;
    int korean, english, math;
    double average;
}std[MAX_STD]; // 구조체 배열의 선언

int main()
{
    printf("==================================================== \n");
    printf("학번 : 2021202058 \n");
    printf("이름 : 송채영 \n");
    printf("==================================================== \n");

    int i;
    double total_average = 0;

    for (int i = 0; i < MAX_STD; i++) {
        printf("%d번째 학생의 학번을 입력하세요 : ", i + 1); // 구조체 배열의 입력
        scanf_s("%d", &(std[i].number));
        printf("%d번째 학생의 국어 점수를 입력하세요 : ", i + 1);
        scanf_s("%d", &(std[i].korean));
        printf("%d번째 학생의 영어 점수를 입력하세요 : ", i + 1);
        scanf_s("%d", &(std[i].english));
        printf("%d번째 학생의 수학 점수를 입력하세요 : ", i + 1);
        scanf_s("%d", &(std[i].math));
        std[i].average = (double)(std[i].korean + std[i].english + std[i].math) / 3; // 각 학생의 평균 구하기
        printf("\n");
    }

    for (int i = 0; i < MAX_STD; i++)
    {
        printf("%d번째 학생의 평균은 %f 입니다. \n", i + 1, std[i].average);
    }
    return 0;
}
