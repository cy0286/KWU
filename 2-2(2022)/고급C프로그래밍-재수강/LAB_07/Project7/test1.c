#include <stdio.h> 

struct STUDENT //�л� ���� ����ü 
{
    char name[20]; //�̸� 
    char subject[5][30]; //����� 
    int hakjum_unit[5]; //�̼������ð� 
    double jumsu[5]; //���� ���� 
    double grade; //������ 
};

int main()
{
    //�ʱ� �л� ���� 
    struct STUDENT stu = { "ȫ�浿",
                            "C/C++", "JAVA", "��ǻ�û��", "ȸ���̷�",
                            "�ʱ��Ϻ���",
                             3, 3, 2, 4, 3,
                             4.5, 3.0, 3.5, 4.0, 3.5, 0.0 }; //������ 
    stu.grade = ((stu.hakjum_unit[0] * stu.jumsu[0]) + (stu.hakjum_unit[1] * stu.jumsu[1])
        + (stu.hakjum_unit[2] * stu.jumsu[2]) + (stu.hakjum_unit[3] * stu.jumsu[3]) +
        (stu.hakjum_unit[4] * stu.jumsu[4])) / (stu.hakjum_unit[0] + stu.hakjum_unit[1] +
            stu.hakjum_unit[2] + stu.hakjum_unit[3] + stu.hakjum_unit[4]);

    printf("==========================================================================================================\n"); 
    printf("���� ����  ���� ����  ���� ����  ����  ����  ���� ����  ����    ������\n"); 
    printf("==========================================================================================================\n"); 
    printf("%s, %s:%d:%.1f, %s:%d:%.1f, %s:%d:%.1f, %s:%d:%.1f,% s: % d : % .1f, = > % .2f", stu.name, stu.subject, stu.hakjum_unit[0], stu.jumsu[0], 
    stu.subject[1], stu.hakjum_unit[1], stu.jumsu[1], stu.subject[2], stu.hakjum_unit[2], stu.jumsu[2], stu.subject[3], stu.hakjum_unit[3], stu.jumsu[3], stu.subject[4], stu.hakjum_unit[4], stu.jumsu[4], stu.grade);
    return 0;
}