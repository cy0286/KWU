#include <stdio.h>
#include <math.h>

#define FIXED_POINT_BITS 8 // 2 integer + 6 fractinal
#define FIXED_POINT_SCALE (1 << 6) // 2^6 for fractional part

float f1(float x) // floating-point 함수
{
    return x * x * x + 4 * x * x - 10;
}

short f2(short x) // fixed-point 함수
{
    // 고정 소수점 형식으로 변환
    short x_squared = x * x / FIXED_POINT_SCALE; // x^2
    short x_cubed = x * x_squared / FIXED_POINT_SCALE; // x^3
    short result = x_cubed + (4 * x_squared) - (10 * FIXED_POINT_SCALE); // x^3 + 4x^2 - 10
    return result;
}

float bisection_float(float a, float b, float tolerance)
{
    float c; //중간점 c를 저장하는 변수
    int max_iter = 100; // 최대 반복 횟수

    for (int i = 1; i < max_iter; i++)
    {
        c = (a + b) / 2; // a와 b의 중간점 계산
        float fc = f1(c); // 중간점에서 f1(c) 값 계산

        // 현재 반복 횟수, a, b, c, f(c) 값 출력
        printf("Iteration %d: a1=%f, b1=%f, c1=%f, f(c1)=%f\n", i, a, b, c, fc);

        if (fabs(fc) < tolerance) // f(c)가 허용 오차보다 작으면
        {
            return c; // c를 반환하고 종료
        }

        if (fc * f1(a) < 0) // f(a)와 f(c)의 부호가 다르면
        {
            b = c; // b를 c로 업데이트
        }
        else
        {
            a = c; // a를 c로 업데이트
        }
    }
    return c; // c 반환
}

short bisection_fixed(short a, short b, short tolerance)
{
    short c; //중간점 c를 저장하는 변수
    int max_iter = 100; // 최대 반복 횟수

    for (int i = 1; i < max_iter; i++)
    {
        c = (a + b) / 2; // a와 b의 중간점 계산
        short fc = f2(c); // 중간점에서 f2(c) 값 계산

        int integer_part_a = a / FIXED_POINT_SCALE; // a를 고정 소수점 스케일로 나눈 정수 부분
        int fractional_part_a = (a % FIXED_POINT_SCALE) * 1000000 / FIXED_POINT_SCALE; // a를 고정 소수점 스케일로 나눈 나머지를 1000000으로 곱한 후 스케일로 나눈 소수 부분
        int integer_part_b = b / FIXED_POINT_SCALE; // b를 고정 소수점 스케일로 나눈 정수 부분
        int fractional_part_b = (b % FIXED_POINT_SCALE) * 1000000 / FIXED_POINT_SCALE; // b를 고정 소수점 스케일로 나눈 나머지를 1000000으로 곱한 후 스케일로 나눈 소수 부분
        int integer_part_c = c / FIXED_POINT_SCALE; // c를 고정 소수점 스케일로 나눈 정수 부분
        int fractional_part_c = (c % FIXED_POINT_SCALE) * 1000000 / FIXED_POINT_SCALE; // c를 고정 소수점 스케일로 나눈 나머지를 1000000으로 곱한 후 스케일로 나눈 소수 부분
        int integer_part_fc = fc / FIXED_POINT_SCALE; // fc를 고정 소수점 스케일로 나눈 정수 부분
        int fractional_part_fc = abs(fc % FIXED_POINT_SCALE) * 1000000 / FIXED_POINT_SCALE; // fc를 고정 소수점 스케일로 나눈 나머지의 절댓값을 1000000으로 곱한 후 스케일로 나눈 소수 부분

        // 현재 반복 횟수, a, b, c, f(c) 값 출력
        printf("Iteration %d: a2=%d.%06d, b2=%d.%06d, c2=%d.%06d, f(c2)=%d.%06d\n", i, integer_part_a, fractional_part_a, integer_part_b, fractional_part_b, integer_part_c, fractional_part_c, integer_part_fc, fractional_part_fc);

        if (abs(fc) < tolerance || c == a || c == b) // f(c)가 허용 오차보다 작거나 c가 a 또는 b와 같으면
        {
            return c; // c를 반환하고 종료
        }

        if (fc * f2(a) < 0) // f(a)와 f(c)의 부호가 다르면
        {
            b = c; // b를 c로 업데이트
        }
        else
        {
            a = c; // a를 c로 업데이트
        }
    }

    return c; // c 반환
}

int main()
{
    float a_float = 1.0, b_float = 2.0, tol_float = 0.0001; // floating-point 변수, 허용 오차 설정
    float root_float = bisection_float(a_float, b_float, tol_float); // 함수 호출

    printf("Floating-point root: %.6f\n\n", root_float); // floating-point 결과 출력

    short a_fixed = 1 * FIXED_POINT_SCALE, b_fixed = 2 * FIXED_POINT_SCALE, tol_fixed = 1; // fixed-point 변수, 허용 오차 설졍
    short root_fixed = bisection_fixed(a_fixed, b_fixed, tol_fixed); // 함수 호출

    //fixed-point 정수 부분, 소수 부분 계산
    int integer_part = root_fixed / FIXED_POINT_SCALE;
    int fractional_part = (root_fixed % FIXED_POINT_SCALE) * 1000000 / FIXED_POINT_SCALE;

    printf("Fixed-point root: %d.%06d\n", integer_part, fractional_part); // fixed-point 결과 출력

    return 0;
}