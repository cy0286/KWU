///////////////////////////////////////////////////////////////////////////////									     
// File Name : 20212058_advanced_ls.c  					     //
// Date : 2023/04/05							     //	
// Os : Ubuntu 16.04 LTS 64bits 		    			     //
// Author : Song ChaeYoung					             //	
// Student ID : 2021202058						     //	
// ------------------------------------------------------------------------- //	
// Title : System Programming Assignment #1-2       			     //
// Description : This program is a simple implementation of the 'ls' command,//
//		 listing the files and directories in the specified directory//
//		along with permissions, owners, groups, sizes, and	     //	
//		modification times. The program first checks to see if the   //
//		argument has been passed. If arguments are not passed, the   //
//		program lists all files and directories in the current       //
//		directory. When the argument is passed, the program lists all//
//		files and directories in the specified directory. Save the   //
//		names of the files and directories, sort them, and output    //
//		them according to the options.				     //
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#define MAX_PATH_LEN 1024 //최대 경로 길이 상수
#define MAX_FILES 1000 //디렉토리 내 최대 파일 개수

///////////////////////////////////////////////////////////////////////////////									     
// sort					     			             //
// ========================================================================= //	
// Description: Given an array of file names and its count,                  //
//		sorts the array in ascending order based on file names.	     //
// 		If the first character of a file name is '.', it is treated  //
//		as a hidden file. The comparison is case-insensitive.	     //	
// Parameters: filename - an array of file names to be sorted		     //
//	       file_count - the number of files in the array		     //
///////////////////////////////////////////////////////////////////////////////
//파일 이름을 기준으로 정렬하는 함수
void sort(char filename[][1024], int file_count)
{
    char temp[1024];
	
    //파일 이름 배열 순회
    for (int i = 0; i < file_count - 1; i++)
    {
        for (int j = i+1; j < file_count; j++)
        {
                //파일 이름의 첫 글자가 .인지 확인
		char hidden_file1[1024];
            	char hidden_file2[1024];

		if(filename[i][0] == '.') //첫 번째 파일 이름의 첫 글자가 숨김 파일이면

		{
			for(int k = 0; k<strlen(filename[i]);k++) //filename[i]의 길이만큼 반복
			{
				hidden_file1[k] = filename[i][k+1]; //첫 글자를 제외한 이름 저장
			}
		}
		else //숨김 파일이 아니면
		{
			strcpy(hidden_file1,filename[i]); //이름 저장
		}
		if(filename[j][0] == '.') //두 번째 파일 이름의 첫 글자가 숨김 파일이면
		{
			for(int k = 0; k<strlen(filename[j]);k++) //filename[j]의 길이만큼 반복
			{
				hidden_file2[k] = filename[j][k+1]; //첫 글자를 제외한 이름 저장
			}
		}
		else //숨김 파일이 아니면
		{
			strcpy(hidden_file2,filename[j]); //이름 저장
		}
            	if(strcasecmp(hidden_file1,hidden_file2)>0) //대소문자 구분 없이 비교
         	{   
            		strcpy(temp,filename[i]);
           		strcpy(filename[i],filename[j]);
            		strcpy(filename[j],temp);
         	}

    	}
    }
}

///////////////////////////////////////////////////////////////////////////////									     
// print_file_info					     	             //
// ========================================================================= //	
// Description: It performs a function of outputting file information for    //
//		a given file path. Use the stat function to read the	     //
//		information in the file, and then output the file type,      //
//		permission, number of links, owner, group, file size, and    //
//		modification time.					     //
// Parameters: filpath - File path with file information to output    	     //
///////////////////////////////////////////////////////////////////////////////
// 파일 정보 출력 함수
void print_file_info(char* filepath) 
{
    struct stat filestat; //파일의 정보를 읽어 구조체 변수 filestat에 저장
    stat(filepath, &filestat);

    //파일 유형, 허가권, 링크 수, 소유자, 그룹, 파일 크기, 수정 시간 출력
    printf("%c%c%c%c%c%c%c%c%c%c  ", 
            S_ISDIR(filestat.st_mode) ? 'd' : '-',
            filestat.st_mode & S_IRUSR ? 'r' : '-',
            filestat.st_mode & S_IWUSR ? 'w' : '-',
            filestat.st_mode & S_IXUSR ? 'x' : '-',
            filestat.st_mode & S_IRGRP ? 'r' : '-',
            filestat.st_mode & S_IWGRP ? 'w' : '-',
            filestat.st_mode & S_IXGRP ? 'x' : '-',
            filestat.st_mode & S_IROTH ? 'r' : '-',
            filestat.st_mode & S_IWOTH ? 'w' : '-',
            filestat.st_mode & S_IXOTH ? 'x' : '-');
    struct passwd *pw;
    struct group *gr;
    pw = getpwuid(filestat.st_uid); //uid에 대한 사용자 정보 구조체 가져오기
    gr = getgrgid(filestat.st_gid); //gid에 대한 그룹 정보 구조체 가져오기
    printf("%4d\t  ", (int)filestat.st_nlink); //링크 수 출력
    printf("%s\t", pw->pw_name); //소유자 이름 출력
    printf("%s\t", gr->gr_name); //그룹 이름 출력
    printf("%8lld\t  ", (long long)filestat.st_size); //파일 크기 출력

    char* modtime = ctime(&filestat.st_mtime); //수정 시간 문자열로 변환
    modtime[strlen(modtime) - 1] = '\0'; //문자열 끝에 있는 개행 문자 제거
    printf("%s  ", modtime); //수정 시간 출력
    printf("%s\n", filepath); //파일 경로 출력
}

///////////////////////////////////////////////////////////////////////////////									     
// list_files					     	             	     //
// ========================================================================= //	
// Description: A function that outputs a list of files in an input 	     //
//		directory. It is divided into files and directories, and the //
//		file is printed according to the options.		     //
// Parameters: dirname - Save the directory path to output		     //
//	       option - Options to apply when outputting a list of files     //
///////////////////////////////////////////////////////////////////////////////
//디렉토리 내의 파일 목록을 출력하는 함수
void list_files(char* dirname, int option) 
{
	DIR* dirp; 
	char directorypath[1024]; //현재 경로를 저장할 배열
	struct stat filestat; //파일 정보를 저장할 구조체
    if(dirname == NULL) //입력받은 경로가 없으면
    {
        dirp = opendir("."); //현재 디렉토리 열기
    }
    else //인자가 있으면
    {
        dirp = opendir(dirname);
    }
    if (dirname != NULL && dirp == NULL) //파일이면
    {
	if(option == 0 || option == 1) //옵션이 없거나, -a옵션일때
	{
            printf("%s\n", dirname); //파일이름 출력
        }
        else //옵션이 -l이거나 -al일때
        {
	    if(dirname[0] =='/') //절대 경로이면
	    {
		printf("Directory path: %s\n",dirname);
	    }
	    else //상대 경로이면
	    {
		getcwd(directorypath,1024); //현재 경로 저장
		printf("Directory path: %s/%s\n",directorypath,dirname);
	    }
	    stat(dirname,&filestat); //파일 정보 구조체에 저장
	    printf("total: %d\n",(int)filestat.st_blocks/2); //파일의 블록 수 출력
            print_file_info(dirname); //파일 정보 출력
        }
	    return;
    }
	
	char filenames[MAX_FILES][MAX_PATH_LEN]; //파일 이름을 저장할 배열을 선언
	int file_count = 0; //파일 개수 0으로 초기화
    
	struct dirent* dp; 

    if(option == 0) //옵션이 없을 때
    {
        while ((dp = readdir(dirp)) != NULL) //디렉토리 내의 모든 파일을 순회
        {
	    strcpy(filenames[file_count],dp->d_name); //파일 이름을 배열에 저장
    	    if (filenames[file_count][0] == '.') //"."과 ".."은 건너뜀
            {
		continue;
            }
            else
            {
                file_count++; //파일 개수 증가
            }
        }
        sort(filenames, file_count); //파일 이름 정렬

        for (int i = 0; i < file_count; i++) 
	{
    	    printf("%s\n", filenames[i]); //파일 이름 출력
        }
    }
    else if(option == 1) //a옵션일때
    {
        while ((dp = readdir(dirp)) != NULL) //디렉토리 내의 모든 파일을 
        {
            strcpy(filenames[file_count],dp->d_name); //파일 이름을 배열에 저장   
            file_count++;
        }
        sort(filenames, file_count);
        for (int i = 0; i < file_count; i++) 
	{
    	    printf("%s\n", filenames[i]);
        }
    }
    else if(option == 2) //l옵션일때
    {
	int block=0;
        while ((dp = readdir(dirp)) != NULL) //디렉토리 내의 모든 파일을 순회
        {
	    strcpy(filenames[file_count],dp->d_name); //파일 이름을 배열에 저장
    	    if (filenames[file_count][0] == '.') //"."과 ".."은 건너뜀
            {
       		    continue;
            }
            else
            {
                file_count++;
            }
        }
        sort(filenames, file_count);
	if(dirname == NULL)
	{
		getcwd(directorypath,1024);
		printf("Directory path: %s\n",directorypath);
	}
	
	else
	{
		if(dirname[0] =='/')
		{
			printf("Directory path: %s\n",dirname);
		}
		else
		{
			getcwd(directorypath,1024);
			printf("Directory path: %s/%s\n",directorypath,dirname);
		}
	}
	for(int i = 0; i<file_count;i++)
	{
		stat(filenames[i],&filestat);
		block += filestat.st_blocks;
		
	}
	printf("total: %d\n",block/2);
        for (int i = 0; i < file_count; i++) 
	{
    	    print_file_info(filenames[i]); //파일 정보 출력
        }
    }
    else //al옵션일때
    {
	int block= 0;
        while ((dp = readdir(dirp)) != NULL) //디렉토리 내의 모든 파일을 
        {
            strcpy(filenames[file_count],dp->d_name); //파일 이름을 배열에 저   
            file_count++;
        }
        sort(filenames, file_count);
	if(dirname == NULL)
	{
		getcwd(directorypath,1024);
		printf("Directory path: %s\n",directorypath);
	}
	
	else
	{
		if(dirname[0] =='/')
		{
			printf("Directory path: %s\n",dirname);
		}
		else
		{
			getcwd(directorypath,1024);
			printf("Directory path: %s/%s\n",directorypath,dirname);
		}
	}
	for(int i = 0; i<file_count;i++)
	{
		stat(filenames[i], &filestat);
		block += filestat.st_blocks;
		
	}
	printf("total: %d\n",block/2);
        for (int i = 0; i < file_count; i++) 
	{
    	    print_file_info(filenames[i]); //파일 정보 출력
        }
    }
	closedir(dirp); //디렉토리 닫기
}

int main(int argc, char** argv)
{
    int aflag = 0, lflag = 0;
    int c = 0;
    char listfile2[1024][1024]; //파일 이름 저장 배열
    int file_count=0;
    while((c = getopt(argc, argv, "al")) != -1) //명령줄 parsing
    {
        switch(c)
        {
            case 'a': //a옵션일때
			 aflag++;
               		 break;

            case 'l': //l옵션일때
                	lflag++;
               		break;

            case '?': //알 수 없는 옵션이 들어왔을 때
                	printf("unknown option character\n");
                	break;
        }
    }

    

    if(argc == optind) //인자가 없을 때
    {
        if(aflag && lflag) //a 옵션과 l 옵션이 모두 적용된 경우
        {
            list_files(NULL, 3); //list_files 함수를 호출 
        }
        else if(aflag) //a 옵션만 적용된 경우
        {
            list_files(NULL, 1);
        }
        else if(lflag) //l 옵션만 적용된 경우
        {
            list_files(NULL, 2);
        }
        else //모두 적용되지 않은 경우
        {
            list_files(NULL, 0);
        }
    }
    else //명령줄 인자가 있는 경우
    {
	struct stat filestat; //파일의 상태 정보를 저장할 구조체
	for(int i = optind;i<argc;i++) //인자로 주어진 파일들에 대해 반복
	{
		if(stat(argv[i],&filestat) == -1)//파일 정보를 얻는데 실패했을 때
		{
			printf("Cannot access %s: No such file or directory\n",argv[i]);
		}
		else //파일 정보를 얻는데 성공했을 때
		{
			strcpy(listfile2[file_count],argv[i]); //파일 이름을 배열에 복사
			file_count++; //파일 개수 증가
		}

	}
        for(int i = 0; i < file_count; i++) //aflag와 lflag에 따라 list_files 함수 호출
        {
            if(aflag && lflag) //옵션이 모두 있는 경우
            {
                list_files(listfile2[i], 3); //각 파일에 대해 모든 정보 출력
            }
            else if(aflag) //a 옵션이 있는 경우
            {
                list_files(listfile2[i], 1);
            }
            else if(lflag) //la 옵션이 있는 경우
            {
                list_files(listfile2[i], 2);
            }
            else //옵션이 없는 경우
            {
                list_files(listfile2[i], 0);
            }
        }
    }
    return 0;
}
