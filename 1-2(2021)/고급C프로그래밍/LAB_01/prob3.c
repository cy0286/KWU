#include<stdio.h>
#define SIZE 10
void odd_num(int n[]);  // Ȧ�� ��� �Լ� ����
void even_num(int n[]); // ¦�� ��� �Լ� ����

int main(void) {
	printf("==================================================== \n");
	printf("�й� : 2021202058 \n");
	printf("�̸� : ��ä�� \n");
	printf("==================================================== \n");

	int number[SIZE];
	int i;
	printf("10���� ���� �Է�\n"); // �ݺ����� �̿��Ͽ� ���� 10�� �Է�
	for (i = 0; i < SIZE; i++) {
		printf("�Է� :  ");
		scanf_s("%d", &number[i]);
	}
	odd_num(number); // Ȧ�� ��� �Լ� ȣ��
	even_num(number); // ¦�� ��� �Լ� ȣ��
	return 0;
}
void odd_num(int n[]) { //Ȧ�� �Լ�
	int i;
	printf("Ȧ�� ��� : ");
	for (i = 0; i < SIZE; i++) {
		if (n[i] % 2 == 1) // 2�� ���� �������� 1�϶� Ȧ��
			printf("%d, ", n[i]);
	}
	printf("\n");
}
void even_num(int n[]) { // ¦�� �Լ�
	printf("¦�� ��� : ");
	for (int i = 0; i < SIZE; i++) {
		if (n[i] % 2 == 0) // 2�� ���� �������� 0�϶� ¦��
			printf("%d, ", n[i]);
	}
	printf("\n");
}