#include <stdio.h> 
int main()
{
	int i;
	int dan; // ����� ���� �Է� ���� ������. 
	printf("����ϰ� ���� ���� �Է� : ");
	scanf_s("%d", &dan); // ����� ���� �Է� �޴´�. 
	for (i = 1; i <= 9; i++) {  //1���� 9���� �ݺ��ϸ� �Է��� ���� ����Ѵ�. 
		printf("%d X %d= %d\n", dan, i, dan * i);
	}
}