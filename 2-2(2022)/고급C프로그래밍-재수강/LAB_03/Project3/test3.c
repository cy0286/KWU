#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
void format_display(char money[]);

int main()
{
	char money[100]; // ���ڿ� ����
	printf("������ �� �ݾ� �Է��ϰ� Enter > ");
	scanf("%s", money);
	format_display(money);
	return 0;
}

void format_display(char money[]) // ���ڿ��� ���ڸ� �Է� �޾� õ ���� ���� ǥ�� ��� �Լ� 
{
	int i, len;
	const char* str = money; // ���̸� ���� ���ڿ�
	len = strlen(str);
	for (i = 0; i < strlen(str); i++) // 3�ڸ� ���� �޸� ���
	{
		printf("%c", money[i]);
		len--; // 3�ڸ� ������ ����ϱ� ���� ��
		if (len % 3 == 0 && len != 0) // �޸� �߰�
		{
			printf(",");
		}
	}
	return 0;
}
