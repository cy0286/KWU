#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
void get(double, int*, double*); //�����ο� �Ǽ��η� ������ �Լ� 
int main()
{
	double value = 0;
	int integer; //����
	double real; //�Ǽ� 
	printf("�Ǽ��� �Է��ϼ��� : ");
	scanf("%lf", &value); //�Ǽ� �Է� 
	get(value, &integer, &real); //�����ο� �Ǽ��η� ������ �Լ��� �� �־��� 
	printf("������ : %d\n", integer);
	printf("�Ǽ��� : %f\n", real);
	return 0;
}
void get(double value, int* integer, double* real) //�����ο� �Ǽ��η� ������ �Լ� 
{
	*integer = (int)value;
	*real = value - *integer;
}