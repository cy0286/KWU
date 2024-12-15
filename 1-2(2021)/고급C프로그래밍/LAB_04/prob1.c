#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 

int main(void)
{	
	printf("==================================================== \n학번 : 2021202058 \n이름 : 송채영\n==================================================== \n");

	char fileName[] = "99.txt"; 
	int i, j; 
	FILE* outFile = NULL; 
	
	//출력파일 생성 
	printf("출력파일 99.txt 생성\n"); 
	if((outFile = fopen(fileName, "wt")) == NULL ) // outFile 파일포인터 변수에 fopen()함수로 출력할 파일을 텍스트 출력모드로 생성함
	{ 
		exit(-1); 
	}
	
	//구구단 파일에 출력 
	printf("출력파일 99.txt에 구구단 출력 시작\n");
	for(i = 1; i <= 9; i++)
	{ 
		for (j = 1; j <= 9; j++)
		{ 
			fprintf(outFile, "%d * %d = %d\n", i, j, i*j); 
		} 
		fprintf(outFile, "\n"); 
	}
	printf("출력파일 99.txt에 구구단 출력 완료\n"); 
	
	//파일 출력이 끝나고 파일 닫음
	printf("출력파일 99.txt 닫음\n"); 
	fclose(outFile);
	return 0; 
}