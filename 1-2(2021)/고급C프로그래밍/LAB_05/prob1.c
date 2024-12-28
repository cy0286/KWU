#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define NAME_LEN	20
#define NUM_LEN		20
#define TEL_LEN		20
#define MAX_PERSON_NUM		100

typedef struct _Person // ������� ������ �����ϴ� ����ü
{
	char name[NAME_LEN];
	char number[NUM_LEN];
	char phone[TEL_LEN];
} Person;

void ShowMenu(void); // �޴� ��� 
void InsertTelInfo(Person*, int*); // �̸�, �й�, ��ȭ��ȣ ������ ���� 
void RemoveTelInfo(Person*, int*); // �й����� �����͸� �˻��Ͽ� �����Ͱ� ���� ��� �ش� �л� ������ ������
void SearchTelInfo(Person*, int); // �й����� �����͸� �˻��Ͽ� �����Ͱ� ���� ��� �ش� �л� ������ �����
void PrintAll(Person*, int); // ��ü ������ ��� 
void LoadData(Person*, int*); // �ؽ�Ʈ ���Ϸκ��� ������ ���� 
void StoreData(Person*, int); // �ؽ�Ʈ ���Ϸ� ��ü ������ ����

int main(void)
{
	printf("==================================================== \n");
	printf("�й� : 2021202058 \n");
	printf("�̸� : ��ä�� \n");
	printf("==================================================== \n");

	int choice;
	Person perArr[MAX_PERSON_NUM];
	int perNum = 0;
	LoadData(perArr, &perNum);

	while (1)
	{
		ShowMenu();
		printf("Choose the item : ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			InsertTelInfo(perArr, &perNum);
			break;
		case 2:
			RemoveTelInfo(perArr, &perNum);
			break;
		case 3:
			SearchTelInfo(perArr, perNum);
			break;
		case 4:
			PrintAll(perArr, perNum);
			break;
		case 5:
			StoreData(perArr, perNum);
			return 0;
		default:
			printf("Data Loaded...... \n");
			break;
		}
	}
	return 0;
}

void ShowMenu(void) // �޴� ����
{
	printf("\n---------Menu--------\n");
	printf("0. Data Load\n");
	printf("1. Insert \n");
	printf("2. Delete \n");
	printf("3. Search \n");
	printf("4. Print All\n");
	printf("5. Data Save & Exit\n");
	printf("\n---------------------\n");
}

void InsertTelInfo(Person* parr, int* pnum)
{
	char name[NAME_LEN], number[NUM_LEN], phone[TEL_LEN];  // ������� ������ �����ϴ� �Լ� 
	printf("[ INSERT ] \n");
	printf("Input Name : "); scanf("%s", name);
	printf("Input Student ID : "); scanf("%s", number);
	printf("Input Tel Number : "); scanf("%s", phone);

	strcpy(parr[*pnum].name, name);
	strcpy(parr[*pnum].number, number);
	strcpy(parr[*pnum].phone, phone);
	(*pnum)++;

	printf("--------> Data Inserted......\n");
}

void RemoveTelInfo(Person* parr, int* pnum) // ������� ������ �����ϴ� �Լ�
{
	int i, j;
	char number[NUM_LEN];
	printf("[ Remove ] \n");
	printf("Input Student ID for Removing : "); scanf("%s", number);

	for (i = 0; i < *pnum; i++)
	{
		if (strcmp(parr[i].number, number) == 0)
		{
			for (j = i + 1; j < *pnum; j++)
			{
				strcpy(parr[j - 1].number, parr[j].number);
			}
			printf("-------> Data Removed......\n");
			(*pnum)--;
			return;
		}
	}
	printf("-------> Data Not Found......\n");
}

void SearchTelInfo(Person* parr, int num) // ������� ������ �˻��ϴ� �Լ� 
{
	int i;
	char number[NUM_LEN];
	printf("[ Search ] \n");
	printf("Input Student ID for Searching : "); scanf("%s", number);

	for (i = 0; i < num; i++)
	{
		if (strcmp(parr[i].number, number) == 0)			
		{
			printf("---> Name : %s / Student ID : %s / Tel : %s  \n",
				parr[i].name, parr[i].number, parr[i].phone);
			return;
		}
	}
	printf("--------> Data Not Found......\n");
}

void PrintAll(Person* parr, int num) // ����� ��� ������ ����ϴ� �Լ�
{
	int i;
	printf("[ Print All Data ] \n");
	for (i = 0; i < num; i++)
		printf("---> Name : %s / Student ID : %s / Tel : %s \n", parr[i].name, parr[i].number, parr[i].phone);
}

void LoadData(Person* parr, int* pnum)
{
	FILE* file = fopen("data.txt", "rt");
	if (file == NULL)
	{
		return;
	}

	while (1)
	{
		fscanf(file, "%s %s %s", parr[*pnum].name, parr[*pnum].number, parr[*pnum].phone);
		if (feof(file) != 0)
			break;
		(*pnum)++;
	}
}

void StoreData(Person* parr, int num) // �����ϴ� �Լ�
{
	int i;
	FILE* file = fopen("data.txt", "wt");
	if (file == NULL)
	{
		printf("file open error!\n");
		return;
	}
	printf("-------> Data Saved......\n");
	for (i = 0; i < num; i++)
		fprintf(file, "%s %s %s \n", parr[i].name, parr[i].number, parr[i].phone);
}