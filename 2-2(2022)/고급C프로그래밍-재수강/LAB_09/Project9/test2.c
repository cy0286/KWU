#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
int main(void)
{
	//힙 영역에 구조체 형태의 노드 생성 
	struct EMP {
		char name[20];
		int age;
		char address[40];
	}*ptr;
	while (1)
	{
		ptr = (struct EMP*)malloc(sizeof(struct EMP)); //메모리 할당요청 
		if (ptr == NULL) //할당한 공간이 없는 경우 
		{
			printf("Heap영역 할당오류! \n");
			exit(1);
		}
		printf("\n성명 ? (입력종료:end) ");
		gets(ptr->name);
		if (!strcmp(ptr->name, "end"))
			break;
		printf("나이 ? ");
		scanf("%d%*c", &ptr->age);
		printf("주소 ? ");
		gets(ptr->address);
	}
	free(ptr); //메모리 해제 

	printf("\n%s, %d, %s \n\n", ptr->name, ptr->age, ptr->address);

	return 0;
}