#include <stdio.h> 
int main()
{
	int i;
	int dan; // 계산할 단을 입력 받을 변수다. 
	printf("출력하고 싶은 단을 입력 : ");
	scanf_s("%d", &dan); // 계산할 단을 입력 받는다. 
	for (i = 1; i <= 9; i++) {  //1부터 9까지 반복하며 입력한 단을 출력한다. 
		printf("%d X %d= %d\n", dan, i, dan * i);
	}
}