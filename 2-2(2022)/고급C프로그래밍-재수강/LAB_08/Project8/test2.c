#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 

enum depcode { Triangle = 1, Rectangle, Circle }type; //도형 종류 열거 정의 

struct shape //도형 데이터 구조체 정의 
{
	int type;
	union
	{
		struct //삼각형 데이터 
		{
			int base, height; //밑변 높이 
		}tri;
		struct //사각형 데이터 
		{
			int width, height; //가로 세로 
		}rec;
		struct //원 데이터 
		{
			int radius; //반지름 
		}cir;
	}u;
}s;

int main()
{
	//출력 
	printf("도형의 타입을 입력하시오(1, 2, 3): ");
	scanf("%d", &type);

	switch (type)
	{
	case Triangle:
		printf("밑변과 높이를 입력하시오( 예를 들어서 100 200 ): ");
		scanf("%d%d", &s.u.tri.base, &s.u.tri.height);
		printf("면적은 %d", (int)(0.5 * s.u.tri.base * s.u.tri.height));
		break;
	case Rectangle:
		printf("가로와 세로의 길이를 입력하시오( 예를 들어서 100 200 ): ");
		scanf("%d%d", &s.u.rec.width, &s.u.rec.height);
		printf("면적은 %d", (int)(s.u.rec.width * s.u.rec.height));
		break;
	case Circle:
		printf("반지름을 입력하시오( 예를 들어서 100): ");
		scanf(" %d", &s.u.cir.radius);
		printf("면적은 %d", (int)(3.14 * s.u.cir.radius * s.u.cir.radius));
		break;
	}
	return 0;
}