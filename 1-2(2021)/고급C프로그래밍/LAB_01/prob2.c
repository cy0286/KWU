#include<stdio.h>
int main()
{
    printf("==================================================== \n");
    printf("학번 : 2021202058 \n");
    printf("이름 : 송채영 \n");
    printf("==================================================== \n");

    int array[8] = { 1, 2, 3, 4, 5, 6, 7, 8 }; 
    printf("array 배열 값 : 1 2 3 4 5 6 7 8 \n");
    printf("shift 된 array 배열 값 : ");
    printf("%d, %d, %d, %d, %d, %d, %d, %d \n",  array[7], array[0], array[1], array[2], array[3], array[4], array[5], array[6]); // 배열출력
    return 0;
}