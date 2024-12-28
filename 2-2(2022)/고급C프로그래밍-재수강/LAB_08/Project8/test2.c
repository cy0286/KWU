#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 

enum depcode { Triangle = 1, Rectangle, Circle }type; //���� ���� ���� ���� 

struct shape //���� ������ ����ü ���� 
{
	int type;
	union
	{
		struct //�ﰢ�� ������ 
		{
			int base, height; //�غ� ���� 
		}tri;
		struct //�簢�� ������ 
		{
			int width, height; //���� ���� 
		}rec;
		struct //�� ������ 
		{
			int radius; //������ 
		}cir;
	}u;
}s;

int main()
{
	//��� 
	printf("������ Ÿ���� �Է��Ͻÿ�(1, 2, 3): ");
	scanf("%d", &type);

	switch (type)
	{
	case Triangle:
		printf("�غ��� ���̸� �Է��Ͻÿ�( ���� �� 100 200 ): ");
		scanf("%d%d", &s.u.tri.base, &s.u.tri.height);
		printf("������ %d", (int)(0.5 * s.u.tri.base * s.u.tri.height));
		break;
	case Rectangle:
		printf("���ο� ������ ���̸� �Է��Ͻÿ�( ���� �� 100 200 ): ");
		scanf("%d%d", &s.u.rec.width, &s.u.rec.height);
		printf("������ %d", (int)(s.u.rec.width * s.u.rec.height));
		break;
	case Circle:
		printf("�������� �Է��Ͻÿ�( ���� �� 100): ");
		scanf(" %d", &s.u.cir.radius);
		printf("������ %d", (int)(3.14 * s.u.cir.radius * s.u.cir.radius));
		break;
	}
	return 0;
}