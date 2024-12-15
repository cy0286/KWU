#include<stdio.h>

enum human { adult = 1, teenager, child, baby }; // 열거형 정의

int main()
{
	printf("==================================================== \n");
	printf("학번 : 2021202058 \n");
	printf("이름 : 송채영 \n");
	printf("==================================================== \n");

	enum human p1 = adult;
	enum human p2 = teenager;
	enum human p3 = child;
	enum human p4 = baby;

	int a; // 수강인원 변수 a 선언
	int b = 0; // 수강가격 변수 b선언 후 초기화
	printf("수강인원? ");
	scanf_s("%d", &a);

	for (int i = 0; i < a; i++)
	{
		int c; // 수강자 나이 변수 c 선언
		printf("%d번 수강자선택 (1.어른 2.청소년 3.아동 4.유아) ; ", i + 1);
		scanf_s("%d", &c);

		if (c == p1)
			b += 15000;
		else if (c == p2)
			b += 12000;
		else if (c == p3)
			b += 8000;
		else if (c == p4)
			b += 3000;
	}
	printf("총 수강가격=%d\n", b);
	return 0;
}
