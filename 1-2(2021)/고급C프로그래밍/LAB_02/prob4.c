#include<stdio.h>

enum human { adult = 1, teenager, child, baby }; // ������ ����

int main()
{
	printf("==================================================== \n");
	printf("�й� : 2021202058 \n");
	printf("�̸� : ��ä�� \n");
	printf("==================================================== \n");

	enum human p1 = adult;
	enum human p2 = teenager;
	enum human p3 = child;
	enum human p4 = baby;

	int a; // �����ο� ���� a ����
	int b = 0; // �������� ���� b���� �� �ʱ�ȭ
	printf("�����ο�? ");
	scanf_s("%d", &a);

	for (int i = 0; i < a; i++)
	{
		int c; // ������ ���� ���� c ����
		printf("%d�� �����ڼ��� (1.� 2.û�ҳ� 3.�Ƶ� 4.����) ; ", i + 1);
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
	printf("�� ��������=%d\n", b);
	return 0;
}
