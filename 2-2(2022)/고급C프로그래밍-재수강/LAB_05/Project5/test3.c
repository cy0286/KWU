#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h> 
#include<string.h> 
int main(int argc, char* argv[]) //char* argv = char **argv, arcg�� ���� �Լ��� ���޵Ǵ� ������ ����, argv�� ���ڿ��� �迭(�����Լ��� ���޵Ǵ� ����)
{
	char msg[10][50]; //���ڿ��� ������ �迭 
	printf("argc : %d\n", argc);
	printf("��ɾ� ���� ���ڿ��� ����� msg 2���� ���ڹ迭\n");
	int i;
	for (i = 0; i < argc; i++)
	{
		strcpy(msg[i], argv[i + 1]); //argv[0]�� ���α׷��� �����ΰ� �� 
		printf("%s\n", msg[i]); //���ڿ� ��� 
	}
	return 0;
}