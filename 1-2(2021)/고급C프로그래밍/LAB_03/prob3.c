#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)

int main()
{
	printf("==================================================== \n");
	printf("학번 : 2021202058 \n");
	printf("이름 : 송채영 \n");
	printf("==================================================== \n");

	char str[32] = "";
	int i = 0;
	int transGap = 'a' - 'A';
	printf("Enter string: ");
	scanf("%s", str);
	printf("Length of string : %d\n", strlen(str));
	for (i = 0; i < strlen(str); i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z') str[i] -= transGap; // 소문자를 대문자로 변환
		else if (str[i] >= 'A' && str[i] <= 'Z') str[i] += transGap; // 대문자를 소문자로 변환
	}
	printf("Result string : %s\n", str);
	return 0;
}
