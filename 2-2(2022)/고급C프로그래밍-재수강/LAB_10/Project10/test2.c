#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 

int main(void)
{
	FILE* fp; //파일 포인터 선언 
	char str[20] = "fileinout test"; //크기가 20인 char형 배열 선언 후 문자열 할당 
	int ch;
	
	fp = fopen("a.txt", "rt"); //파일 열기 읽기 모드 
	ch = fgetc(fp); //fp 파일로 부터 한글자 읽어오기 
	while (fgetc(fp) != EOF); //파일의 끝을 만날 때 까지 반복
	fgets(str, sizeof(str), fp); //파일로부터 한 줄 읽기 
	printf("%s", str); //출력 
	fclose(fp); //파일 닫기 
	return 0;
}