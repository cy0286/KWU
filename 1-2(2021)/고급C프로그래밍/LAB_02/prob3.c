#include <stdio.h>

struct triangle // 구조체 배열 선언
{
    int a, b, c;
};

int classification(triangle tri);

int main()
{
    printf("==================================================== \n");
    printf("학번 : 2021202058 \n");
    printf("이름 : 송채영 \n");
    printf("==================================================== \n");

    struct triangle tri;

    while (1)
    {

        printf("삼각형의 세변의 길이를 입력받습니다. 0 0 0 이 입력되면 종료합니다. \n\n");

        printf("삼각형의 세 변의 길이를 입력하세요 : "); 
        scanf_s("%d, %d, %d", &tri.a, &tri.b, &tri.c); // 길이 구조체 변수 값

        if (tri.a == 0 && tri.b == 0 && tri.c == 0)
        {
            break;
        }
        else // 삼각형 판별 호출
            classification(tri.a, tri.b, tri.c);
    }
    return 0;
}

int classification(triangle tri) // 삼각형 판별
{
    if (tri.a == tri.b && tri.b == tri.c && tri.c == tri.a)
    {
        printf("입력하신 삼각형은 정삼각형입니다.\n\n");
    }

    else if (tri.a == tri.b && tri.a != tri.c || tri.b == tri.c && tri.b != tri.a || tri.c == tri.a && tri.c != tri.b)
    {
        printf("입력하신 삼각형은 이등변 삼각형입니다.\n\n");
    }

    else if (tri.a >= tri.b + tri.c || tri.b >= tri.a + tri.c || tri.c >= tri.a + tri.b)
    {
        printf("입력하신 변들로는 삼각형을 만들 수 없습니다.\n\n");
    }

    else
    {
        printf("입력하신 삼각형은 그냥 삼각형입니다.\n\n");
    }
}
