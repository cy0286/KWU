#include <stdio.h>
#include <string.h> 
#pragma warning(disable:4996)

int main()
{
	printf("==================================================== \n");
	printf("학번 : 2021202058 \n");
	printf("이름 : 송채영 \n");
	printf("==================================================== \n");

	char inputStr[10][15], temp[15];
	int i = 0, j = 0, max = 10;
	printf("입력을 종료하려면 그냥 엔터를 누르세요.\n");
	fseek(stdin, 01, SEEK_END);

	//입력 
	for (i = 0; i < 10; i++)
	{
		printf("%d번째? ", i + 1);
		gets(temp);

		//문자열 길이 점검 
		if (strlen(temp) == 0)
		{
			max = i;
			break;
		}
		strcpy(inputStr[i], temp);
	}

	//정렬	
	for (i = max; i >= 0; i--)
	{
		for (j = max; j > i; j--)
		{
			if (strcmp(inputStr[i], inputStr[j]) > 0)
			{
				strcpy(temp, inputStr[i]);
				strcpy(inputStr[i], inputStr[j]);
				strcpy(inputStr[j], temp);
			}
		}
	}

	//출력 
	for (i = 0; i < max; i++)
	{
		printf("%s ", inputStr[i]);
	}
	puts("");
	return 0;
}
