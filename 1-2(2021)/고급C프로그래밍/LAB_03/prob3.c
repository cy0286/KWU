#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)

int main()
{
	printf("==================================================== \n");
	printf("�й� : 2021202058 \n");
	printf("�̸� : ��ä�� \n");
	printf("==================================================== \n");

	char str[32] = "";
	int i = 0;
	int transGap = 'a' - 'A';
	printf("Enter string: ");
	scanf("%s", str);
	printf("Length of string : %d\n", strlen(str));
	for (i = 0; i < strlen(str); i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z') str[i] -= transGap; // �ҹ��ڸ� �빮�ڷ� ��ȯ
		else if (str[i] >= 'A' && str[i] <= 'Z') str[i] += transGap; // �빮�ڸ� �ҹ��ڷ� ��ȯ
	}
	printf("Result string : %s\n", str);
	return 0;
}
