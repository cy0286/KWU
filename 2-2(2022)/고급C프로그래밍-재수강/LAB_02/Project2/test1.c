#include <stdio.h> 
int main()
{
	int i, * p, arr[] = { 5, 10, 15, 20, 25 }; // int�� ���� i, int�� ������ p, int�� �迭 ����, �迭�� �ʱ�ȭ
	printf("arr[0] is %d.\n", arr[0]); // ù��° �迭�� ��� 
	printf("arr is %d.\n", *arr); // �迭�� �ּҿ� *�����ڸ� �̿��� �迭�� ��� 
	p = arr; // ������ ���� p�� arr�� ����Ŵ 
	for (i = 0; i < 5; i++)
		printf("%d\t", *(p + i)); // p�迭�� i��° ����� ���� ��� 
	printf("\n");
	p = arr; // ������ ���� p�� arr�� ����Ŵ 
	for (i = 0; i < 5; i++)
		printf("%d\t", *p++); // p�� �ּҸ� �� ĭ �ű� ���� ��� 
	printf("\n");
	p = arr; // ������ ���� p�� arr�� ����Ŵ 
	for (i = 0; i < 5; i++)
		printf("%d\t", (*p)++); // p�� ����Ű�� �ִ� ���� �������� ��� 
	printf("\n");
	return 0;
}