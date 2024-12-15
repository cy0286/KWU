#include<stdio.h>
#define SIZE 10
void odd_num(int n[]);  // 홀수 출력 함수 선언
void even_num(int n[]); // 짝수 출력 함수 선언

int main(void) {
	printf("==================================================== \n");
	printf("학번 : 2021202058 \n");
	printf("이름 : 송채영 \n");
	printf("==================================================== \n");

	int number[SIZE];
	int i;
	printf("10개의 숫자 입력\n"); // 반복문을 이용하여 정수 10개 입력
	for (i = 0; i < SIZE; i++) {
		printf("입력 :  ");
		scanf_s("%d", &number[i]);
	}
	odd_num(number); // 홀수 출력 함수 호출
	even_num(number); // 짝수 출력 함수 호출
	return 0;
}
void odd_num(int n[]) { //홀수 함수
	int i;
	printf("홀수 출력 : ");
	for (i = 0; i < SIZE; i++) {
		if (n[i] % 2 == 1) // 2로 나눈 나머지가 1일때 홀수
			printf("%d, ", n[i]);
	}
	printf("\n");
}
void even_num(int n[]) { // 짝수 함수
	printf("짝수 출력 : ");
	for (int i = 0; i < SIZE; i++) {
		if (n[i] % 2 == 0) // 2로 나눈 나머지가 0일때 짝수
			printf("%d, ", n[i]);
	}
	printf("\n");
}