#define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>  
#include<string.h> 
int main()
{
	int i, count; //반복문에서 사용할 i와 str의 길이를 저장할 count변수 
	char str[100]; //문자열을 저장할 공간 
	printf("문자열을 입력하세요 : ");
	scanf("%s", str); //str에 문자열 입력받기  
	count = strlen(str); //str의 길이를 반환하여 count변수에 저장 
	printf("내용을 거꾸로 출력 ==> ");
	for (i = count; i >= 0; i--) //문자열을 거꾸로 출력하기 위해 count의 값을 이용해 배열의 저장된 문자열중 뒤부터 접근
	{
		printf("%c", str[i]);
	}
	return 0;
}