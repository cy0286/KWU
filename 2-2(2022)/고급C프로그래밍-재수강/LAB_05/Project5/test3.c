#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h> 
#include<string.h> 
int main(int argc, char* argv[]) //char* argv = char **argv, arcg는 메인 함수에 전달되는 정보의 갯수, argv는 문자열의 배열(메인함수에 전달되는 정보)
{
	char msg[10][50]; //문자열을 저장할 배열 
	printf("argc : %d\n", argc);
	printf("명령어 라인 문자열이 저장된 msg 2차원 문자배열\n");
	int i;
	for (i = 0; i < argc; i++)
	{
		strcpy(msg[i], argv[i + 1]); //argv[0]에 프로그램의 실행경로가 들어감 
		printf("%s\n", msg[i]); //문자열 출력 
	}
	return 0;
}