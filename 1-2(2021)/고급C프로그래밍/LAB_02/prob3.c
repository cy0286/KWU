#include <stdio.h>

struct triangle // ����ü �迭 ����
{
    int a, b, c;
};

int classification(triangle tri);

int main()
{
    printf("==================================================== \n");
    printf("�й� : 2021202058 \n");
    printf("�̸� : ��ä�� \n");
    printf("==================================================== \n");

    struct triangle tri;

    while (1)
    {

        printf("�ﰢ���� ������ ���̸� �Է¹޽��ϴ�. 0 0 0 �� �ԷµǸ� �����մϴ�. \n\n");

        printf("�ﰢ���� �� ���� ���̸� �Է��ϼ��� : "); 
        scanf_s("%d, %d, %d", &tri.a, &tri.b, &tri.c); // ���� ����ü ���� ��

        if (tri.a == 0 && tri.b == 0 && tri.c == 0)
        {
            break;
        }
        else // �ﰢ�� �Ǻ� ȣ��
            classification(tri.a, tri.b, tri.c);
    }
    return 0;
}

int classification(triangle tri) // �ﰢ�� �Ǻ�
{
    if (tri.a == tri.b && tri.b == tri.c && tri.c == tri.a)
    {
        printf("�Է��Ͻ� �ﰢ���� ���ﰢ���Դϴ�.\n\n");
    }

    else if (tri.a == tri.b && tri.a != tri.c || tri.b == tri.c && tri.b != tri.a || tri.c == tri.a && tri.c != tri.b)
    {
        printf("�Է��Ͻ� �ﰢ���� �̵ �ﰢ���Դϴ�.\n\n");
    }

    else if (tri.a >= tri.b + tri.c || tri.b >= tri.a + tri.c || tri.c >= tri.a + tri.b)
    {
        printf("�Է��Ͻ� ����δ� �ﰢ���� ���� �� �����ϴ�.\n\n");
    }

    else
    {
        printf("�Է��Ͻ� �ﰢ���� �׳� �ﰢ���Դϴ�.\n\n");
    }
}
