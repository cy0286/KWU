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
		struct EMP* next; //자신과 같은 구조체 주소 참조 
	} *ptr;
	struct EMP* head, * tail, * x, * prev = NULL;
	char s_name[20];
	int found;
	head = tail = NULL;
	while (1)
	{
		ptr = (struct EMP*)malloc(sizeof(struct EMP)); //메모리 할당요청 
		if (ptr == NULL) //할당한 공간이 없는 경우 
		{
			printf("Heap영역 할당오류! \n");
			exit(1); //종료 
		}
		printf("\n성명 ? (입력종료:end) ");
		gets(ptr->name);
		if (!strcmp(ptr->name, "end")) //end입력시 
			break; //탈출 
		printf("나이 ? ");
		scanf("%d%*c", &ptr->age);
		printf("주소 ? ");
		gets(ptr->address);
		ptr->next = NULL;
		//노드간 주소연결 
		if (head == NULL) //첫번째 노드일 때 
			head = tail = ptr;
		else //노드가 추가될 때 
		{
			tail->next = ptr;
			tail = ptr;
		}
	}
	free(ptr); //end 입력된 노드 해제 

	printf("\n");

	//삭제 전 저장된 이름과 메모리주소 출력 
	ptr = head; //링크드리스트 처음부터 검색 
	while (ptr)
	{
		printf("\n%s, %d, %s \n", ptr->name, ptr->age, ptr->address); //출력 
		printf("메모리주소 : %p, %p, %p\n", &(ptr->name), &(ptr->age), &(ptr-> address)); //메모리주소 출력 
		ptr = ptr->next;
	}

	printf("\n\n삭제할 성명 ? ");
	gets(s_name);

	found = 1;
	ptr = head; //링크드리스트 처음부터 검색 
	while (ptr)
	{
		if (!strcmp(s_name, ptr->name))
		{
			if (ptr == head) //노드가 처음이면 
			{
				head = ptr->next;
			}
			else if (ptr == tail) //노드가 끝이면 
			{
				prev->next = NULL;
				tail = prev;
			}
			else //노드가 중간이면
			{
				prev->next = ptr->next;
			}
			found = 0;
			free(ptr); //노드 해제 
			break; //반복문 탈출 
		}
		prev = ptr; //prev는 ptr의 이전 노드주소를 저장함 
		ptr = ptr->next; //다음 노드 주소를 가짐 
	}

	if (found)
		printf("Not found!!! \n");
		printf("\n노드가 삭제된 링크드리스트 출력 \n");
		ptr = head; //링크드리스트 처음부터 출력
		while (ptr)
		{
			printf("%s, %d, %s \n", ptr->name, ptr->age, ptr->address); //삭제 후 저장된 이름
			printf("메모리주소: %p, %p, %p\n", &(ptr->name), &(ptr->age), &(ptr-> address));
			ptr = ptr->next;
		}
		printf("\n");
		ptr = head; //링크드리스트 처음부터 마지막 해제 
		while (ptr)
		{
			x = ptr;
			ptr = ptr->next;
			free(x); //메모리 해제 
		}

		return 0;
}