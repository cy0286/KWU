#include <stdio.h>
#include <math.h>

#define FIXED_POINT_BITS 8 // 2 integer + 6 fractinal
#define FIXED_POINT_SCALE (1 << 6) // 2^6 for fractional part

float f1(float x) // floating-point �Լ�
{
    return x * x * x + 4 * x * x - 10;
}

short f2(short x) // fixed-point �Լ�
{
    // ���� �Ҽ��� �������� ��ȯ
    short x_squared = x * x / FIXED_POINT_SCALE; // x^2
    short x_cubed = x * x_squared / FIXED_POINT_SCALE; // x^3
    short result = x_cubed + (4 * x_squared) - (10 * FIXED_POINT_SCALE); // x^3 + 4x^2 - 10
    return result;
}

float bisection_float(float a, float b, float tolerance)
{
    float c; //�߰��� c�� �����ϴ� ����
    int max_iter = 100; // �ִ� �ݺ� Ƚ��

    for (int i = 1; i < max_iter; i++)
    {
        c = (a + b) / 2; // a�� b�� �߰��� ���
        float fc = f1(c); // �߰������� f1(c) �� ���

        // ���� �ݺ� Ƚ��, a, b, c, f(c) �� ���
        printf("Iteration %d: a1=%f, b1=%f, c1=%f, f(c1)=%f\n", i, a, b, c, fc);

        if (fabs(fc) < tolerance) // f(c)�� ��� �������� ������
        {
            return c; // c�� ��ȯ�ϰ� ����
        }

        if (fc * f1(a) < 0) // f(a)�� f(c)�� ��ȣ�� �ٸ���
        {
            b = c; // b�� c�� ������Ʈ
        }
        else
        {
            a = c; // a�� c�� ������Ʈ
        }
    }
    return c; // c ��ȯ
}

short bisection_fixed(short a, short b, short tolerance)
{
    short c; //�߰��� c�� �����ϴ� ����
    int max_iter = 100; // �ִ� �ݺ� Ƚ��

    for (int i = 1; i < max_iter; i++)
    {
        c = (a + b) / 2; // a�� b�� �߰��� ���
        short fc = f2(c); // �߰������� f2(c) �� ���

        int integer_part_a = a / FIXED_POINT_SCALE; // a�� ���� �Ҽ��� �����Ϸ� ���� ���� �κ�
        int fractional_part_a = (a % FIXED_POINT_SCALE) * 1000000 / FIXED_POINT_SCALE; // a�� ���� �Ҽ��� �����Ϸ� ���� �������� 1000000���� ���� �� �����Ϸ� ���� �Ҽ� �κ�
        int integer_part_b = b / FIXED_POINT_SCALE; // b�� ���� �Ҽ��� �����Ϸ� ���� ���� �κ�
        int fractional_part_b = (b % FIXED_POINT_SCALE) * 1000000 / FIXED_POINT_SCALE; // b�� ���� �Ҽ��� �����Ϸ� ���� �������� 1000000���� ���� �� �����Ϸ� ���� �Ҽ� �κ�
        int integer_part_c = c / FIXED_POINT_SCALE; // c�� ���� �Ҽ��� �����Ϸ� ���� ���� �κ�
        int fractional_part_c = (c % FIXED_POINT_SCALE) * 1000000 / FIXED_POINT_SCALE; // c�� ���� �Ҽ��� �����Ϸ� ���� �������� 1000000���� ���� �� �����Ϸ� ���� �Ҽ� �κ�
        int integer_part_fc = fc / FIXED_POINT_SCALE; // fc�� ���� �Ҽ��� �����Ϸ� ���� ���� �κ�
        int fractional_part_fc = abs(fc % FIXED_POINT_SCALE) * 1000000 / FIXED_POINT_SCALE; // fc�� ���� �Ҽ��� �����Ϸ� ���� �������� ������ 1000000���� ���� �� �����Ϸ� ���� �Ҽ� �κ�

        // ���� �ݺ� Ƚ��, a, b, c, f(c) �� ���
        printf("Iteration %d: a2=%d.%06d, b2=%d.%06d, c2=%d.%06d, f(c2)=%d.%06d\n", i, integer_part_a, fractional_part_a, integer_part_b, fractional_part_b, integer_part_c, fractional_part_c, integer_part_fc, fractional_part_fc);

        if (abs(fc) < tolerance || c == a || c == b) // f(c)�� ��� �������� �۰ų� c�� a �Ǵ� b�� ������
        {
            return c; // c�� ��ȯ�ϰ� ����
        }

        if (fc * f2(a) < 0) // f(a)�� f(c)�� ��ȣ�� �ٸ���
        {
            b = c; // b�� c�� ������Ʈ
        }
        else
        {
            a = c; // a�� c�� ������Ʈ
        }
    }

    return c; // c ��ȯ
}

int main()
{
    float a_float = 1.0, b_float = 2.0, tol_float = 0.0001; // floating-point ����, ��� ���� ����
    float root_float = bisection_float(a_float, b_float, tol_float); // �Լ� ȣ��

    printf("Floating-point root: %.6f\n\n", root_float); // floating-point ��� ���

    short a_fixed = 1 * FIXED_POINT_SCALE, b_fixed = 2 * FIXED_POINT_SCALE, tol_fixed = 1; // fixed-point ����, ��� ���� ����
    short root_fixed = bisection_fixed(a_fixed, b_fixed, tol_fixed); // �Լ� ȣ��

    //fixed-point ���� �κ�, �Ҽ� �κ� ���
    int integer_part = root_fixed / FIXED_POINT_SCALE;
    int fractional_part = (root_fixed % FIXED_POINT_SCALE) * 1000000 / FIXED_POINT_SCALE;

    printf("Fixed-point root: %d.%06d\n", integer_part, fractional_part); // fixed-point ��� ���

    return 0;
}