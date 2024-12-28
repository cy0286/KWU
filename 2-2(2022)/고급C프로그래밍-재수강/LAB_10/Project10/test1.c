#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
int main(void)
{
	FILE* fp; //파일 포인터 선언 
	int line_num = 1; //라인 번호 
	char file[100]; //파일 이름 
	char str[100]; //문자열 
	printf("파일의 이름을 입력하시오: ");
	scanf("%s", file);
	fp = fopen(file, "rt"); //파일 열기 읽기 모드 
	if (fp == NULL) //열기 실패 
	{
		printf("원본 파일 %s를 열 수 없습니다.", file); //에러 출력 
		return -1; //비정상적인 종료 의미 
	}
	while (!feof(fp)) //파일의 끝을 만날 때 까지 반복 
	{
		fgets(str, sizeof(str), fp); //파일로부터 한 줄 읽기 
		printf("%d %s", line_num, str); //라인 번호, 문자 출력 
		line_num++; //라인 번호 +1 
	}
	fclose(fp); //파일 닫기 
	return 0;
}