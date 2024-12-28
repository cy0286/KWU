#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 

enum depcode { software = 1, computerinformation, informationConvergence }d_major; //열거형 학과 정의

struct Student //학생 정보 구조체 정의 
{
    int age; //나이 
    int major; //학과 
    int grade; //학년 
    char name[20]; //이름 
    char address[100]; //주소 
}stu;

int main()
{
    //데이터를 입력 받은 후 구조체에 저장 
    printf("학생에 대한 정보를 입력하시오\n");
    printf("나이: ");
    scanf("%d", &stu.age);
    printf("학년: ");
    scanf("%d", &stu.grade);
    printf("학과: ");
    scanf("%d", &stu.major);
    printf("이름: ");
    scanf("%s", stu.name);
    printf("주소: ");
    scanf("%s", stu.address);

    switch (stu.major)
    {
    software:
        printf("%d", software); //software=1 
        break;
    computerinformation:
        printf("%d", computerinformation); //computerinformation=2 
        break;
    informationConvergence:
        printf("%d", informationConvergence); //informationConvergence=3 
        break;
    default:
        break;
    }

    //출력 
    printf("\n");
    printf("%s\n %d살 %d학년 학과번호:%d\n%s", stu.name, stu.age, stu.grade, stu.major, stu.address);
    return 0;
}