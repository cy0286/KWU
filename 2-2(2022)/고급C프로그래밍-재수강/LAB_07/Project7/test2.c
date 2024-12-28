#include <stdio.h> 

struct STUDENT //학생 정보 구조체 
{
    char name[20]; //이름 
    char subject[5][30]; //과목명 
    int hakjum_unit[5]; //이수단위시간 
    double jumsu[5]; //과목별 학점 
    double grade; //총평점 
};

int main()
{
    //초기 학생 정보 
    struct STUDENT stu1 = { "홍길동",
                            "C/C++", "JAVA", "컴퓨팅사고", "회로이론", "초급일본어",
                            3, 3, 2, 4, 3,
                            4.5, 3.0, 3.5, 4.0, 3.5, 0.0 };
    struct STUDENT stu2 = { "홍길동",
                            "C/C++", "JAVA", "컴퓨팅사고", "회로이론", "초급일본어",
                            3, 3, 2, 4, 3,
                            2.5, 1.0, 4.2, 3.0, 1.5, 2.0 };
    struct STUDENT stu3 = { "홍길동",
                            "C/C++", "JAVA", "컴퓨팅사고", "회로이론", "초급일본어",
                            3, 3, 2, 4, 3,
                            4.0, 3.5, 3.5, 2.0, 1.5, 4.0 }; //총평점 
    stu1.grade = ((stu1.hakjum_unit[0] * stu1.jumsu[0]) + (stu1.hakjum_unit[1] * stu1.jumsu[1]) + (stu1.hakjum_unit[2] * stu1.jumsu[2]) + (stu1.hakjum_unit[3] * stu1.jumsu[3])
    + (stu1.hakjum_unit[4] * stu1.jumsu[4])) / (stu1.hakjum_unit[0] + stu1.hakjum_unit[1] + stu1.hakjum_unit[2] + stu1.hakjum_unit[3] + stu1.hakjum_unit[4]);
    stu2.grade = ((stu2.hakjum_unit[0] * stu2.jumsu[0]) + (stu2.hakjum_unit[1] * stu2.jumsu[1]) + (stu2.hakjum_unit[2] * stu2.jumsu[2]) + (stu2.hakjum_unit[3] * stu2.jumsu[3])
    + (stu2.hakjum_unit[4] * stu2.jumsu[4])) / (stu2.hakjum_unit[0] + stu2.hakjum_unit[1] + stu2.hakjum_unit[2] + stu2.hakjum_unit[3] + stu2.hakjum_unit[4]);
    stu3.grade = ((stu3.hakjum_unit[0] * stu3.jumsu[0]) + (stu3.hakjum_unit[1] * stu3.jumsu[1]) + (stu3.hakjum_unit[2] * stu3.jumsu[2]) + (stu3.hakjum_unit[3] * stu3.jumsu[3])
    + (stu3.hakjum_unit[4] * stu3.jumsu[4])) / (stu3.hakjum_unit[0] + stu3.hakjum_unit[1] + stu3.hakjum_unit[2] + stu3.hakjum_unit[3] + stu3.hakjum_unit[4]);

    printf("==========================================================================================================\n"); 
    printf("성명 과목  학점 과목  학점 과목  학점  과목  학점 과목  학점    총평점\n"); 
    printf("==========================================================================================================\n"); 
    printf("%s, %s:%d:%.1f, %s:%d:%.1f, %s:%d:%.1f, %s:%d:%.1f, % s: % d : % .1f, = > % .2f\n", stu1.name, stu1.subject, stu1.hakjum_unit[0], stu1.jumsu[0], 
    stu1.subject[1], stu1.hakjum_unit[1], stu1.jumsu[1], stu1.subject[2], stu1.hakjum_unit[2],
    stu1.jumsu[2], stu1.subject[3], stu1.hakjum_unit[3], stu1.jumsu[3], stu1.subject[4],
    stu1.hakjum_unit[4], stu1.jumsu[4], stu1.grade);
    printf("%s, %s:%d:%.1f, %s:%d:%.1f, % s: % d : % .1f, % s : % d : % .1f, % s : % d : % .1f, = > % .2f\n", stu2.name, stu2.subject, stu2.hakjum_unit[0], stu2.jumsu[0], 
    stu2.subject[1], stu2.hakjum_unit[1], stu2.jumsu[1], stu2.subject[2], stu2.hakjum_unit[2],
    stu2.jumsu[2], stu2.subject[3], stu2.hakjum_unit[3], stu2.jumsu[3], stu2.subject[4],
    stu2.hakjum_unit[4], stu2.jumsu[4], stu2.grade);
    printf("%s, %s:%d:%.1f, %s:%d:%.1f, % s: % d : % .1f, % s : % d : % .1f, % s : % d : % .1f, = > % .2f", stu3.name, stu3.subject, stu3.hakjum_unit[0], stu3.jumsu[0], 
    stu3.subject[1], stu3.hakjum_unit[1], stu3.jumsu[1], stu3.subject[2], stu3.hakjum_unit[2],
    stu3.jumsu[2], stu3.subject[3], stu3.hakjum_unit[3], stu3.jumsu[3], stu3.subject[4],
    stu3.hakjum_unit[4], stu3.jumsu[4], stu3.grade);
    return 0;
}