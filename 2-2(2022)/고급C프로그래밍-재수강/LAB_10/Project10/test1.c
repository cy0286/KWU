#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
int main(void)
{
	FILE* fp; //���� ������ ���� 
	int line_num = 1; //���� ��ȣ 
	char file[100]; //���� �̸� 
	char str[100]; //���ڿ� 
	printf("������ �̸��� �Է��Ͻÿ�: ");
	scanf("%s", file);
	fp = fopen(file, "rt"); //���� ���� �б� ��� 
	if (fp == NULL) //���� ���� 
	{
		printf("���� ���� %s�� �� �� �����ϴ�.", file); //���� ��� 
		return -1; //���������� ���� �ǹ� 
	}
	while (!feof(fp)) //������ ���� ���� �� ���� �ݺ� 
	{
		fgets(str, sizeof(str), fp); //���Ϸκ��� �� �� �б� 
		printf("%d %s", line_num, str); //���� ��ȣ, ���� ��� 
		line_num++; //���� ��ȣ +1 
	}
	fclose(fp); //���� �ݱ� 
	return 0;
}