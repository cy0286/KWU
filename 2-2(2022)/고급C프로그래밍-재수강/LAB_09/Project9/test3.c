#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
int main(void)
{
	//�� ������ ����ü ������ ��� ���� 
	struct EMP {
		char name[20];
		int age;
		char address[40];
		struct EMP* next; //�ڽŰ� ���� ����ü �ּ� ���� 
	} *ptr;
	struct EMP* head, * tail, * x, * prev = NULL;
	char s_name[20];
	int found;
	head = tail = NULL;
	while (1)
	{
		ptr = (struct EMP*)malloc(sizeof(struct EMP)); //�޸� �Ҵ��û 
		if (ptr == NULL) //�Ҵ��� ������ ���� ��� 
		{
			printf("Heap���� �Ҵ����! \n");
			exit(1); //���� 
		}
		printf("\n���� ? (�Է�����:end) ");
		gets(ptr->name);
		if (!strcmp(ptr->name, "end")) //end�Է½� 
			break; //Ż�� 
		printf("���� ? ");
		scanf("%d%*c", &ptr->age);
		printf("�ּ� ? ");
		gets(ptr->address);
		ptr->next = NULL;
		//��尣 �ּҿ��� 
		if (head == NULL) //ù��° ����� �� 
			head = tail = ptr;
		else //��尡 �߰��� �� 
		{
			tail->next = ptr;
			tail = ptr;
		}
	}
	free(ptr); //end �Էµ� ��� ���� 

	printf("\n");

	//���� �� ����� �̸��� �޸��ּ� ��� 
	ptr = head; //��ũ�帮��Ʈ ó������ �˻� 
	while (ptr)
	{
		printf("\n%s, %d, %s \n", ptr->name, ptr->age, ptr->address); //��� 
		printf("�޸��ּ� : %p, %p, %p\n", &(ptr->name), &(ptr->age), &(ptr-> address)); //�޸��ּ� ��� 
		ptr = ptr->next;
	}

	printf("\n\n������ ���� ? ");
	gets(s_name);

	found = 1;
	ptr = head; //��ũ�帮��Ʈ ó������ �˻� 
	while (ptr)
	{
		if (!strcmp(s_name, ptr->name))
		{
			if (ptr == head) //��尡 ó���̸� 
			{
				head = ptr->next;
			}
			else if (ptr == tail) //��尡 ���̸� 
			{
				prev->next = NULL;
				tail = prev;
			}
			else //��尡 �߰��̸�
			{
				prev->next = ptr->next;
			}
			found = 0;
			free(ptr); //��� ���� 
			break; //�ݺ��� Ż�� 
		}
		prev = ptr; //prev�� ptr�� ���� ����ּҸ� ������ 
		ptr = ptr->next; //���� ��� �ּҸ� ���� 
	}

	if (found)
		printf("Not found!!! \n");
		printf("\n��尡 ������ ��ũ�帮��Ʈ ��� \n");
		ptr = head; //��ũ�帮��Ʈ ó������ ���
		while (ptr)
		{
			printf("%s, %d, %s \n", ptr->name, ptr->age, ptr->address); //���� �� ����� �̸�
			printf("�޸��ּ�: %p, %p, %p\n", &(ptr->name), &(ptr->age), &(ptr-> address));
			ptr = ptr->next;
		}
		printf("\n");
		ptr = head; //��ũ�帮��Ʈ ó������ ������ ���� 
		while (ptr)
		{
			x = ptr;
			ptr = ptr->next;
			free(x); //�޸� ���� 
		}

		return 0;
}