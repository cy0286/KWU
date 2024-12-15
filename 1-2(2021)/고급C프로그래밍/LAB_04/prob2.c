#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <string.h> 

struct student_score 
{ 
	int no; 
	char name[10]; 
	float num1, num2, num3, total; 
}; 
int main()
{	
	printf("==================================================== \n학번 : 2021202058 \n이름 : 송채영\n==================================================== \n");

	int i; 
	int search = 0; 
	struct student_score s1[7] = { 
		{1, "A", 90.2, 90.1, 88.8}, 
		{2, "B", 89.1, 88.5, 90.2}, 
		{3, "C", 92.1, 87.1, 90.1}, 
		{4, "D", 85.3, 86.2, 95.1}, 
		{5, "E", 88.2, 86.3, 91.1}, 
		{6, "F", 98.2, 90.1, 93.5}, 
		{7, "G", 93.3, 95.5, 91.2} 
	}; 
	struct student_score str[7]; 
	
	FILE* fp1; 
	FILE* fp2; 
	fp1 = fopen("score1.txt", "w"); 
	for(i=0; i<7; i++) 
	{ 
		fprintf(fp1, "%d. %s %.1f %.1f %.1f \n", s1[i].no, s1[i].name, s1[i].num1, s1[i].num2, s1[i].num3); 
	} 
	fclose(fp1); 
	fp1 = fopen("score1.txt", "r"); 
	fp2 = fopen("score2.txt", "w"); 
	for(i=0; i<7; i++) 
	{ 
		fscanf(fp1, "%d. %s %f %f %f ", &str[i].no, str[i].name, &str[i].num1, &str[i].num2, &str[i].num3); 
		str[i].total=str[i].num1+str[i].num2+str[i].num3; 
		fprintf(fp2, "%d. %s %.1f %.1f %.1f total : %.1f \n", str[i].no, str[i].name, str[i].num1, str[i].num2, str[i].num3, str[i].total); 
	} 
	
	fseek(fp1, 0, SEEK_END); 
	fclose(fp1);
	fclose(fp2); 
	return 0; 
}

