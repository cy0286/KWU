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
    struct STUDENT stu = { "홍길동",
                            "C/C++", "JAVA", "컴퓨팅사고", "회로이론",
                            "초급일본어",
                             3, 3, 2, 4, 3,
                             4.5, 3.0, 3.5, 4.0, 3.5, 0.0 }; //총평점 
    stu.grade = ((stu.hakjum_unit[0] * stu.jumsu[0]) + (stu.hakjum_unit[1] * stu.jumsu[1])
        + (stu.hakjum_unit[2] * stu.jumsu[2]) + (stu.hakjum_unit[3] * stu.jumsu[3]) +
        (stu.hakjum_unit[4] * stu.jumsu[4])) / (stu.hakjum_unit[0] + stu.hakjum_unit[1] +
            stu.hakjum_unit[2] + stu.hakjum_unit[3] + stu.hakjum_unit[4]);

    printf("==========================================================================================================\n"); 
    printf("성명 과목  학점 과목  학점 과목  학점  과목  학점 과목  학점    총평점\n"); 
    printf("==========================================================================================================\n"); 
    printf("%s, %s:%d:%.1f, %s:%d:%.1f, %s:%d:%.1f, %s:%d:%.1f,% s: % d : % .1f, = > % .2f", stu.name, stu.subject, stu.hakjum_unit[0], stu.jumsu[0], 
    stu.subject[1], stu.hakjum_unit[1], stu.jumsu[1], stu.subject[2], stu.hakjum_unit[2], stu.jumsu[2], stu.subject[3], stu.hakjum_unit[3], stu.jumsu[3], stu.subject[4], stu.hakjum_unit[4], stu.jumsu[4], stu.grade);
    return 0;
}