#include <stdio.h>
#include <string.h> 
#pragma warning(disable:4996)

int main()
{
	printf("==================================================== \n");
	printf("�й� : 2021202058 \n");
	printf("�̸� : ��ä�� \n");
	printf("==================================================== \n");

	char inputStr[10][15], temp[15];
	int i = 0, j = 0, max = 10;
	printf("�Է��� �����Ϸ��� �׳� ���͸� ��������.\n");
	fseek(stdin, 01, SEEK_END);

	//�Է� 
	for (i = 0; i < 10; i++)
	{
		printf("%d��°? ", i + 1);
		gets(temp);

		//���ڿ� ���� ���� 
		if (strlen(temp) == 0)
		{
			max = i;
			break;
		}
		strcpy(inputStr[i], temp);
	}

	//����	
	for (i = max; i >= 0; i--)
	{
		for (j = max; j > i; j--)
		{
			if (strcmp(inputStr[i], inputStr[j]) > 0)
			{
				strcpy(temp, inputStr[i]);
				strcpy(inputStr[i], inputStr[j]);
				strcpy(inputStr[j], temp);
			}
		}
	}

	//��� 
	for (i = 0; i < max; i++)
	{
		printf("%s ", inputStr[i]);
	}
	puts("");
	return 0;
}
