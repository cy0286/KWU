#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 

enum depcode { software = 1, computerinformation, informationConvergence }d_major; //������ �а� ����

struct Student //�л� ���� ����ü ���� 
{
    int age; //���� 
    int major; //�а� 
    int grade; //�г� 
    char name[20]; //�̸� 
    char address[100]; //�ּ� 
}stu;

int main()
{
    //�����͸� �Է� ���� �� ����ü�� ���� 
    printf("�л��� ���� ������ �Է��Ͻÿ�\n");
    printf("����: ");
    scanf("%d", &stu.age);
    printf("�г�: ");
    scanf("%d", &stu.grade);
    printf("�а�: ");
    scanf("%d", &stu.major);
    printf("�̸�: ");
    scanf("%s", stu.name);
    printf("�ּ�: ");
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

    //��� 
    printf("\n");
    printf("%s\n %d�� %d�г� �а���ȣ:%d\n%s", stu.name, stu.age, stu.grade, stu.major, stu.address);
    return 0;
}