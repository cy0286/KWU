#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> //malloc() �Լ� ��� 
#include <string.h> 
int main(void)
{
	//�� ������ ����ü ������ ��� ���� 
	struct EMP {
		char name[20];
		int age;
		char address[40];
	}*ptr;
	ptr = (struct EMP*)malloc(sizeof(struct EMP)); //�޸� �Ҵ��û 
	if (ptr == NULL) //�Ҵ��� ������ ���� ��� 
	{
		printf("Heap���� �Ҵ����!\n");
		exit(1);
	}
	//��� 
	printf("\n���� ? (�Է�����:end) ");
	gets(ptr->name);
	printf("���� ? ");
	scanf("%d%*c", &ptr->age);
	printf("�ּ� ? ");
	gets(ptr->address);
	printf("\n%s, %d, %s \n\n", ptr->name, ptr->age, ptr->address);
	free(ptr); //�޸� ���� 
	return 0;
}