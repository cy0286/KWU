#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <stddef.h> //offsetof�� ���ǵ� ������� 

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
    FILE* fp = NULL; //���� ���� ���� �� �ʱ�ȭ 
    fp = fopen("test.txt", "w"); //���� ���� ���� ��� 

    printf("����ü ũ�� : %d\n", sizeof(struct Student)); //����ü ũ�� ��� 
    //����ü ��ġ ��� 
    printf("����ü ��ġ : %d\n", offsetof(struct Student, age));
    printf("����ü ��ġ : %d\n", offsetof(struct Student, major));
    printf("����ü ��ġ : %d\n", offsetof(struct Student, grade));
    printf("����ü ��ġ : %d\n", offsetof(struct Student, name));
    printf("����ü ��ġ : %d\n", offsetof(struct Student, address));
    printf("\n");

    if (fp == NULL)
    {
        printf("���� ���� ����\n");
    }
    else
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
        printf("%s\n %d�� %d�г� �а���ȣ:%d\n%s", stu.name, stu.age, stu.grade, stu.major,
            stu.address);
        fprintf(fp, "%s\n %d�� %d�г� �а���ȣ:%d\n%s", stu.name, stu.age, stu.grade,
            stu.major, stu.address); //���Ͽ� ���� 
    }

    fclose(fp); //���� ��Ʈ�� ���� 
    return 0;
}