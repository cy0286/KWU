#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#pragma warning(disable:4996)

int count(char*);
int main()
{
	printf("==================================================== \n");
	printf("�й� : 2021202058 \n");
	printf("�̸� : ��ä�� \n");
	printf("==================================================== \n");

	char str[100];
	printf("�ܾ �Է��ϼ��� : ");
	scanf("%s", str);
	strlwr(str); //��ҹ��� �ҹ��ڷ� 
	count(str);
	return 0;
}
int count(char* inputStr)
{
	int countArr[26] = { 0, }; //���ĺ� ������ŭ �迭 ���� 
	int cnt = 0, srcLen = 0, i = 0;
	srcLen = strlen(inputStr); //���ڿ� ���� ���� 
	for (cnt = 0; cnt < srcLen; cnt++)
	{
		if (inputStr[cnt] - 'a' >= 0 && inputStr[cnt] - 'a' <= 122) { //���ĺ��̸� 
			countArr[inputStr[cnt] - 'a']++;
		}
		else continue;
	} //��� 
	for (i = 0; i < 26; i++)
	{
		printf("%c:%d��\n", 97 + i, countArr[i]);
	}
	return 0;
}
