#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 

int main(void)
{
	FILE* fp; //���� ������ ���� 
	char str[20] = "fileinout test"; //ũ�Ⱑ 20�� char�� �迭 ���� �� ���ڿ� �Ҵ� 
	int ch;
	
	fp = fopen("a.txt", "rt"); //���� ���� �б� ��� 
	ch = fgetc(fp); //fp ���Ϸ� ���� �ѱ��� �о���� 
	while (fgetc(fp) != EOF); //������ ���� ���� �� ���� �ݺ�
	fgets(str, sizeof(str), fp); //���Ϸκ��� �� �� �б� 
	printf("%s", str); //��� 
	fclose(fp); //���� �ݱ� 
	return 0;
}