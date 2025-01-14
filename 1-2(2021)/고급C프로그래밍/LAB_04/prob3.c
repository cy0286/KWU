#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <string.h> 

struct student_score 
{ 
	char no[10]; 
	char name[10]; 
	int middle, final, attendance, homework, total; 
	char* grade; 
};

int main() 
{	
	printf("==================================================== \n학번 : 2021202058 \n이름 : 송채영\n==================================================== \n");

	int exit = 0; 
	
	struct student_score student_temp; 
	
	FILE* fp1; 
	
	fp1 = fopen("grade.txt", "w"); 
	
	while (!exit) 
	{ 
		printf("학번:"); 
		scanf("%s", student_temp.no);
		printf("이름:"); 
		scanf("%s", student_temp.name); 
		printf("중간고사:"); 
		scanf("%d", &student_temp.middle); 
		printf("기말고사:"); 
		scanf("%d", &student_temp.final); 
		printf("출석:"); 
		scanf("%d", &student_temp.attendance); 
		printf("과제:"); 
		scanf("%d", &student_temp.homework); 
		
		student_temp.total = student_temp.middle + student_temp.final + student_temp.attendance + student_temp.homework; 
		
		if (student_temp.total >= 95) 
		{ 
			student_temp.grade = "A+"; 
		} 
		else if 
			(student_temp.total >= 90) 
		{ 
			student_temp.grade = "A"; 
		} 
		else if 
			(student_temp.total >= 85) 
		{ 
			student_temp.grade = "B+"; 
		} 
		else if 
			(student_temp.total >= 80) 
		{ 
			student_temp.grade = "B"; 
		} 
		else if 
			(student_temp.total >= 75) 
		{ 
			student_temp.grade = "C+"; 
		}
		else if 
			(student_temp.total >= 70) 
		{ 
			student_temp.grade = "C"; 
		} 
		else 
		{ 
			student_temp.grade = "F";
		} 
		
		fprintf(fp1, "%s %s %2d %2d %2d %2d %3d %s \n", student_temp.no, student_temp.name, student_temp.middle, student_temp.final, student_temp.attendance, student_temp.homework, student_temp.total, student_temp.grade); 
		printf("----------------------------------------------\n학생 정보를 파일에 저장하였습니다.\n"); 
		printf("그만 두시겠습니까? (네:1, 아니요:0) : "); 
		scanf("%d", &exit);
		printf("----------------------------------------------\n");
	} 
	fclose(fp1);
	return 0;
}

