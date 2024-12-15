#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#pragma warning(disable:4996)

int count(char*);
int main()
{
	printf("==================================================== \n");
	printf("학번 : 2021202058 \n");
	printf("이름 : 송채영 \n");
	printf("==================================================== \n");

	char str[100];
	printf("단어를 입력하세요 : ");
	scanf("%s", str);
	strlwr(str); //대소문자 소문자로 
	count(str);
	return 0;
}
int count(char* inputStr)
{
	int countArr[26] = { 0, }; //알파벳 갯수만큼 배열 잡음 
	int cnt = 0, srcLen = 0, i = 0;
	srcLen = strlen(inputStr); //문자열 길이 저장 
	for (cnt = 0; cnt < srcLen; cnt++)
	{
		if (inputStr[cnt] - 'a' >= 0 && inputStr[cnt] - 'a' <= 122) { //알파벳이면 
			countArr[inputStr[cnt] - 'a']++;
		}
		else continue;
	} //출력 
	for (i = 0; i < 26; i++)
	{
		printf("%c:%d개\n", 97 + i, countArr[i]);
	}
	return 0;
}
