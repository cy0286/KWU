#include <stdio.h>

struct time
{
	double t; // 시간 t 구조체 선언
};

int main()
{
	printf("==================================================== \n");
	printf("학번 : 2021202058 \n");
	printf("이름 : 송채영 \n");
	printf("==================================================== \n");

	struct time time_12; // 시간 구조체 변수 선언
	struct time time_24;
	struct time minutes;

	printf("시간을 입력하세요 : ");
	scanf_s("%lf", &minutes);
	time_12 = time_24 = minutes;

	printf("입력하신 시간은 \n");
	printf("12시간짜리 시계로는 '%d시 %.0f분'이고 \n", ((int)time_12.t) % 12, (time_12.t - (int)time_12.t) * 60); // minutes를 정수형 변수로 받음
	printf("24시간짜리 시계로는 '%d시 %.0f분'입니다. \n", ((int)time_24.t) % 24, (time_24.t - (int)time_24.t) * 60);
	return 0;
}
