#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>  
#include<string.h> 
int main()
{
	int i, count; //�ݺ������� ����� i�� str�� ���̸� ������ count���� 
	char str[100]; //���ڿ��� ������ ���� 
	printf("���ڿ��� �Է��ϼ��� : ");
	scanf("%s", str); //str�� ���ڿ� �Է¹ޱ�  
	count = strlen(str); //str�� ���̸� ��ȯ�Ͽ� count������ ���� 
	printf("������ �Ųٷ� ��� ==> ");
	for (i = count; i >= 0; i--) //���ڿ��� �Ųٷ� ����ϱ� ���� count�� ���� �̿��� �迭�� ����� ���ڿ��� �ں��� ����
	{
		printf("%c", str[i]);
	}
	return 0;
}