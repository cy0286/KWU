#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 

int main(void)
{	
	printf("==================================================== \n�й� : 2021202058 \n�̸� : ��ä��\n==================================================== \n");

	char fileName[] = "99.txt"; 
	int i, j; 
	FILE* outFile = NULL; 
	
	//������� ���� 
	printf("������� 99.txt ����\n"); 
	if((outFile = fopen(fileName, "wt")) == NULL ) // outFile ���������� ������ fopen()�Լ��� ����� ������ �ؽ�Ʈ ��¸��� ������
	{ 
		exit(-1); 
	}
	
	//������ ���Ͽ� ��� 
	printf("������� 99.txt�� ������ ��� ����\n");
	for(i = 1; i <= 9; i++)
	{ 
		for (j = 1; j <= 9; j++)
		{ 
			fprintf(outFile, "%d * %d = %d\n", i, j, i*j); 
		} 
		fprintf(outFile, "\n"); 
	}
	printf("������� 99.txt�� ������ ��� �Ϸ�\n"); 
	
	//���� ����� ������ ���� ����
	printf("������� 99.txt ����\n"); 
	fclose(outFile);
	return 0; 
}