#include<stdio.h>

void reverse(int*, int);

int main()
{
    printf("==================================================== \n");
    printf("학번 : 2021202058 \n");
    printf("이름 : 송채영 \n");
    printf("==================================================== \n");

    int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }; // 길이가 10인 int형 변수 선언 후 초기화
    int i;
    printf("초기 배열 값 : ");
    for(int i = 0; i < 10; i++) {
        printf(" %d", arr[i]);
    }
    printf("\n");
    reverse(arr, 10);
    return 0;
}

void reverse(int* A, int size) {
    int i;
    printf("변환 후 배열 값 : ");
    for (i = size - 1; i >= 0; i--) {
        printf("%d ", A[i]); // 역순으로 출력
    }
    printf("\n");
}
