#include <stdio.h>

struct time
{
	double t; // �ð� t ����ü ����
};

int main()
{
	printf("==================================================== \n");
	printf("�й� : 2021202058 \n");
	printf("�̸� : ��ä�� \n");
	printf("==================================================== \n");

	struct time time_12; // �ð� ����ü ���� ����
	struct time time_24;
	struct time minutes;

	printf("�ð��� �Է��ϼ��� : ");
	scanf_s("%lf", &minutes);
	time_12 = time_24 = minutes;

	printf("�Է��Ͻ� �ð��� \n");
	printf("12�ð�¥�� �ð�δ� '%d�� %.0f��'�̰� \n", ((int)time_12.t) % 12, (time_12.t - (int)time_12.t) * 60); // minutes�� ������ ������ ����
	printf("24�ð�¥�� �ð�δ� '%d�� %.0f��'�Դϴ�. \n", ((int)time_24.t) % 24, (time_24.t - (int)time_24.t) * 60);
	return 0;
}
