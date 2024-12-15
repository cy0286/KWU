///////////////////////////////////////////////////////////////////////////////
// File Name : 2021202058_html_ls.c				    	     //
// Date :  2023/04/18			                                     //
// Os : Ubuntu 16.04 LTS 64bits 	    				     //
// Author : Song ChaeYoung                                		     //
// Student ID : 2021202058			                             //
// ------------------------------------------------------------------------- //
// Title : System Programming Assignment #2-1       			     //
// Description : This is a C program that implements the basic functionality //
//	of the 'ls' command on Linux. Programs list files and directories    //
//	in the current directory or in the specified directory and sort them //
//	by specific criteria. The program also supports a variety of options,//
//	including '-a' to display hidden files, '-l' to display file details,//
//	'-h' to display file sizes in human-readable formats, and '-S' to    //
//	sort by file size, '-r' is sorted in reverse order. This program also//
//	supports wildcard patterns. When a wildcard pattern is given as an   //
//	argument, the program uses the 'glob' function to find all files     //
//	that match the pattern and add them to the list of files or          //
//	directories to be processed. In this practice, we added a code to    //
//	implement the ls command implemented above in html and print it out. //
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
#include <ctype.h>
#include <glob.h>

#define MAX_PATH_LEN 1024 // 최대 경로 길이 상수
#define MAX_FILES 1000    // 디렉토리 내 최대 파일 개수

///////////////////////////////////////////////////////////////////////////////
// sort					     			             //
// ========================================================================= //
// Description: Given an array of file names and its count, sorts the array  //
//	in ascending order based on file names. If the first character of a  //
//	file name is '.', it is treated as a hidden file. The comparison is  //
//	case-insensitive. Sorts the file name array according to the options //
//	you select, and uses selection sort as the sort. If Sflag is true,   //
//	sort the file names according to the file size, and if the file names//
//	are the same, compare and sort the strings converted to capital      //
//	letters. If rflag is true, sort the file name array in reverse order.//
// Parameters: Sflag - Flag determines whether to sort by file size	     //
//	       rflag - Flag to determine if file names should be sorted in   //
//	       reverse e order						     //
//             path - File path						     //
//	       filename - an array of file names to be sorted		     //
//	       file_count - the number of files in the array		     //
///////////////////////////////////////////////////////////////////////////////
void sort(int Sflag, int rflag, char *path, char filename[][1024], int file_count); // 파일 이름 정렬 함수
void print_file_info(int hflag, char *filepath, char *filename); // 파일 정보 출력 함수
void print_human_readable_size(double size); // 사람이 읽을 수 있는 형식으로 파일 크기를 출력하는 함수
void list_files(int aflag, int lflag, int hflag, int Sflag, int rflag, char *dirname); // 디렉토리 내 파일 리스트를 출력하는 함수
int wildcardpattern(const char *str); // 문자열에 와일드카드 패턴이 있는지 검사하는 함수
FILE *file; // 파일 포인터를 가리키는 전역 변수 file

// 파일 이름을 기준으로 선택 정렬하는 함수
void sort(int Sflag, int rflag, char *path, char filename[][1024], int file_count)
{
   char temp[1024];
   char temp2[1024];
   char temppath[1024]; // 경로 임시 저장

   // 파일 이름 배열 순회
   for (int i = 0; i < file_count - 1; i++)
   {
      for (int j = i + 1; j < file_count; j++)
      {
         // 파일 이름의 첫 글자가 .인지 확인
         char hidden_file1[1024];
         char hidden_file2[1024];

         if (filename[i][0] == '.') // 첫 번째 파일 이름의 첫 글자가 숨김 파일이면
         {
            for (int k = 0; k < strlen(filename[i]); k++) // filename[i]의 길이만큼 반복
            {
               hidden_file1[k] = filename[i][k + 1]; // 첫 글자를 제외한 이름 저장
            }
         }
         else // 숨김 파일이 아니면
         {
            strcpy(hidden_file1, filename[i]); // 이름 저장
         }
         if (filename[j][0] == '.') // 두 번째 파일 이름의 첫 글자가 숨김 파일이면
         {
            for (int k = 0; k < strlen(filename[j]); k++) // filename[j]의 길이만큼 반복
            {
               hidden_file2[k] = filename[j][k + 1]; // 첫 글자를 제외한 이름 저장
            }
         }
         else // 숨김 파일이 아니면
         {
            strcpy(hidden_file2, filename[j]); // 이름 저장
         }
         // 대문자로 변환
         for (int k = 0; hidden_file1[k]; k++)
         {
            hidden_file1[k] = toupper(hidden_file1[k]);
         }
         for (int k = 0; hidden_file2[k]; k++)
         {
            hidden_file2[k] = toupper(hidden_file2[k]);
         }
         if (Sflag) // S 옵션을 선택한 경우
         {
            struct stat file1, file2; // 파일 정보 저장 구조체
            if (path == NULL) // 경로가 지정되지 않은 경우
            {
               strcpy(temppath, filename[i]); // 첫 번째 파일의 정보를 저장
               stat(temppath, &file1);
               strcpy(temppath, filename[j]); // 두 번째 파일의 정보를 저장
               stat(temppath, &file2);
            }
            else // 경로가 지정된 경우
            {
               strcpy(temppath, path); // 경로와 파일 이름을 합침
               strcat(temppath, "/");
               strcat(temppath, filename[i]);
               stat(temppath, &file1); // 첫 번째 파일의 정보를 저장
               strcpy(temppath, path); // 경로와 파일 이름을 합침
               strcat(temppath, "/");
               strcat(temppath, filename[j]); 
               stat(temppath, &file2); // 두 번째 파일의 정보를 저장
            }

            if (file1.st_size < file2.st_size) // 첫 번째 파일의 크기가 두 번째 파일의 크기보다 작은 경우
            {
               // 첫 번째 파일과 두 번째 파일의 이름을 교환
               strcpy(temp, filename[i]); 
               strcpy(filename[i], filename[j]);
               strcpy(filename[j], temp);
            }
            else if (file1.st_size == file2.st_size && strcmp(hidden_file1, hidden_file2) > 0) // 크기가 같은 경우
            {
               // 첫 번째 파일과 두 번째 파일의 이름을 교환
               strcpy(temp, filename[i]);
               strcpy(filename[i], filename[j]);
               strcpy(filename[j], temp);
            }
         }
         else
         {
            if (strcmp(hidden_file1, hidden_file2) > 0) // 대문자로 변환한 문자열 비교
            {
               strcpy(temp, filename[i]);
               strcpy(filename[i], filename[j]);
               strcpy(filename[j], temp);
            }
         }
      }
   }
   if (rflag) // r옵션을 선택한 경우
   {
      for (int i = 0; i < file_count / 2; i++) // 파일 이름을 역순으로 정렬
      {
         strcpy(temp2, filename[i]);
         strcpy(filename[i], filename[file_count - i - 1]);
         strcpy(filename[file_count - i - 1], temp2);
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
//		modification time. When outputting the file size, call the   //
//		print_human_readable_size function to output the file size   //
//		in human-readable format if the hflag value is nonzero.	     //
// Parameters:  hflag - Flag indicating whether to output file size in 	     //
//			human-readable format				     //
//		filpath - File path with file information to output	     //
//		filename - File name					     //
///////////////////////////////////////////////////////////////////////////////
// 파일 정보 출력 함수
void print_file_info(int hflag, char *filepath, char *filename)
{
   struct stat filestat; // 파일의 정보를 읽어 구조체 변수 filestat에 저장
   
   char path[1024]; // 파일 경로 저장할 변수
   char permission[11]; // 파일 권한 정보 저장할 변수

   if (filepath != filename) // 파일 경로가 존재하는 경우, 파일 경로를 만들어 stat 함수로 파일의 정보를 읽음
   {
      strcpy(path, filepath);
      strcat(path, "/");
      strcat(path, filename);
      lstat(path, &filestat); // lstat 함수를 사용해 파일의 정보를 읽음
   }

   else // 파일 경로가 없는 경우 파일명으로 정보를 읽음
   {
      strcpy(path, filename);
      lstat(path, &filestat);
   }

   struct passwd *pw; // 파일의 소유자 정보를 저장할 구조체 변수
   struct group *gr; // 파일의 그룹 정보를 저장할 구조체 변수 
   
   // 파일 유형, 허가권, 링크 수, 소유자, 그룹, 파일 크기, 수정 시간 출력
   if(S_ISDIR(filestat.st_mode)) {permission[0] = 'd';} // 파일 유형이 디렉토리인 경우
   else if(S_ISLNK(filestat.st_mode)) {permission[0] = 'l';}  // 파일 유형이 링크인 경우
   else{permission[0] = '-';} // 그 외 경우 "-"로 표시
   // 파일 허가권 정보 설정
   filestat.st_mode &S_IRUSR ? (permission[1] = 'r') : (permission[1] = '-'); // User read 권한
   filestat.st_mode &S_IWUSR ? (permission[2] = 'w') : (permission[2] = '-'); // User write 권한
   filestat.st_mode &S_IXUSR ? (permission[3] = 'x') : (permission[3] = '-'); // User execute 권한
   filestat.st_mode &S_IRGRP ? (permission[4] = 'r') : (permission[4] = '-'); // Group read 권한
   filestat.st_mode &S_IWGRP ? (permission[5] = 'w') : (permission[5] = '-'); // Group write 권한
   filestat.st_mode &S_IXGRP ? (permission[6] = 'x') : (permission[6] = '-'); // Group execute 권한
   filestat.st_mode &S_IROTH ? (permission[7] = 'r') : (permission[7] = '-'); // Others read 권한
   filestat.st_mode &S_IWOTH ? (permission[8] = 'w') : (permission[8] = '-'); // Others write 권한
   filestat.st_mode &S_IXOTH ? (permission[9] = 'x') : (permission[9] = '-'); // Others execute 권한
   permission[10]='\0'; // 문자열 끝에 null 문자 추가
   printf("%s\t", permission); // 파일 허가권 정보 출력

   pw = getpwuid(filestat.st_uid); // uid에 대한 사용자 정보 구조체 가져오기
   gr = getgrgid(filestat.st_gid); // gid에 대한 그룹 정보 구조체 가져오기

   if (S_ISDIR(filestat.st_mode)) // 디렉토리인 경우 파란색
   {
      fprintf(file, "<tr style = \"color: blue\">");
   }
   else if (S_ISLNK(filestat.st_mode)) // link 파일인 경우 녹색
   {
      fprintf(file, "<tr style = \"color: green\">");
   }
   else // 그 외 경우 빨간색
   {
      fprintf(file, "<tr style = \"color: red\">");
   }

   fprintf(file, "<td><a href = \"%s\">%s</a></td>\n", path,filename); // HTML table에 파일 이름 출력
   fprintf(file, "<td>%s</td>", permission); // 파일 권한 출력
   printf("%4d\t  ", (int)filestat.st_nlink); // 링크 수 출력
   printf("%s\t", pw->pw_name); // 소유자 이름 출력
   printf("%s\t", gr->gr_name); // 그룹 이름 출력
   fprintf(file, "<td>%4d</td><td>%s</td><td>%s</td>", (int)filestat.st_nlink, pw->pw_name, gr->gr_name);
   if (hflag != 0) // hflag가 0이 아닌 경우 파일 크기를 human-readable 형태로 출력
   {
      print_human_readable_size((double)filestat.st_size); // 함수호출
   }
   else // hflag가 0인 경우
   {
      printf("%8lld\t", (long long)filestat.st_size); // 파일 크기 출력
      fprintf(file, "<td>%8lld</td>", (long long)filestat.st_size); // 파일 크기 출력
   }
   char *modtime = ctime(&filestat.st_mtime); // 수정 시간 문자열로 변환
   modtime[strlen(modtime) - 1] = '\0'; // 문자열 끝에 있는 개행 문자 제거
   printf("%s  ", modtime); // 수정 시간 출력
   printf("%s\n", filename); // 파일 경로 출력
   fprintf(file, "<td>%s</td></tr>", modtime); // HTML table에 파일 수정 시간 출력
}

///////////////////////////////////////////////////////////////////////////////
// print_human_readable_size					             //
// ========================================================================= //
// Description: A function that outputs the file size passed as a factor in  //
//		human-readable form.   					     //
// Parameters: 	size - File size	   				     //
///////////////////////////////////////////////////////////////////////////////
// 인자로 전달된 파일 크기에 대한 단위를 계산하여 출력하는 함수
void print_human_readable_size(double size)
{
   const char *units[] = {" ", "K", "M", "G"}; // 단위 배열
   int i = 0; // 단위 인덱스
   while (size > 1024) // 1024를 넘어가면 단위를 증가시키며 나누기
   {
      size /= 1024;
      i++;
   }
   printf("%.1f%s\t", size, units[i]); // 소수점 자리까지 출력
   fprintf(file, "<td>%1.f%s</td>", size, units[i]); // HTML 파일에 출력
}

///////////////////////////////////////////////////////////////////////////////
// list_files					     	             	     //
// ========================================================================= //
// Description: A function that outputs a list of files in an input 	     //
//		directory. It is divided into files and directories, and the //
//		file is printed according to the flag.		     	     //
// Parameters:  aflag - Flag that determines whether hidden files are also   //
//			printed						     //
//		lflag - Flag that determines whether to output more 	     //
//			information					     //
//		hflag - Flag that determines whether to output file size in  //
//			human-readable units				     //
//		Sflag - Flag that determines whether to sort file names by   //
//			size						     //
//		rflag - Flag that determines whether to output file names in //
//			reverse order					     //
//		dirname - Save the directory path to output		     //
///////////////////////////////////////////////////////////////////////////////
// 디렉토리 내의 파일 목록을 출력하는 함수
void list_files(int aflag, int lflag, int hflag, int Sflag, int rflag, char *dirname)
{
   DIR *dirp; // 디렉토리 포인터
   char directorypath[1024]; // 현재 경로를 저장할 배열
   struct stat filestat; // 파일 정보를 저장할 구조체
   char filenames[MAX_FILES][MAX_PATH_LEN]; // 파일 이름을 저장할 배열을 선언
   int file_count = 0; // 파일 개수 0으로 초기화
   struct dirent *dp; // 디렉토리 엔트리 구조체 포인터

   dirp = opendir(dirname); // 디렉토리 열기
   realpath(dirname, directorypath); // 절대 경로로 변환하여 저장

   if (dirname != NULL && dirp == NULL) // 파일이면
   {
      if (lflag != 0) // -l 옵션이 켜져있을 경우
      {
         printf("Directory path: %s\n", directorypath); // 현재 디렉토리 경로 출력
         fprintf(file, "<b> Directory path : %s</b><br>", directorypath); // HTML 파일에 출력
         stat(dirname, &filestat); // 파일 정보 구조체에 저장
         printf("%s\n", dirname); // 파일 이름 출력
         printf("total: %d\n", (int)filestat.st_blocks / 2); // 파일의 블록 수 출력
         fprintf(file, "<b> total %d</b><br>", (int)filestat.st_blocks / 2); // HTML 파일에 출력
         fprintf(file, "<table border = \"1\">\n"); // HTML 파일에 테이블 태그 삽입
         fprintf(file, "<tr><th>Name</th><th>Permission</th><th>Link</th><th>Owner</th><th>Group</th><th>Size</th><th>Last Modified</th></tr>\n"); // HTML 파일에 테이블 헤더 삽입
         print_file_info(hflag, dirname, dirname); // 파일 정보 출력
      }
      else // -l 옵션이 꺼져있을 경우
      {
         fprintf(file, "<table border = \"1\">\n"); // HTML 파일에 테이블 태그 삽입
         fprintf(file, "<tr><th>Name</th></tr>\n"); // HTML 파일에 파일 이름 헤더 삽입
         printf("%s\n", dirname); // 파일이름 출력
         fprintf(file, "<b><td>%s</td></b>\n", dirname); // HTML 파일에 출력
      }
      fprintf(file, "</table>\n"); // HTML 파일에 테이블 태그 닫기
   }
   else // 디렉토리일 경우
   {
      if (aflag == 0) // -a 옵션이 꺼져있을 경우
      {
         while ((dp = readdir(dirp)) != NULL) // 디렉토리 내의 모든 파일을 순회
         {
            strcpy(filenames[file_count], dp->d_name); // 파일 이름을 배열에 저장
            if (strcmp(dp->d_name, "html_ls.html") == 0) // html_ls.html 파일은 건너뜀
            {
               continue;
            }
            if (filenames[file_count][0] == '.') //"."과 ".."은 건너뜀
            {
               continue;
            }
            else // 그 외 파일
            {
               file_count++; // 파일 개수 증가
            }
         }
      }
      else // -a 옵션이 켜져있을 경우
      {
         while ((dp = readdir(dirp)) != NULL) // 디렉토리 내의 모든 파일을
         {
            if (strcmp(dp->d_name, "html_ls.html") == 0) // html_ls.html 파일은 건너뛰기
            {
               continue;
            }
            strcpy(filenames[file_count], dp->d_name); // 파일 이름을 배열에 저장
            file_count++; //파일 개수를 증가
         }
      }

      sort(Sflag, rflag, dirname, filenames, file_count); // 파일 이름 정렬 함수 호출

      if (lflag != 0) // -l 옵션이 켜져있을 경우
      {
         int block; // 디렉토리 내 모든 파일의 블록 수의 합
         char path[1024]; // 경로와 파일 이름을 저장할 문자열

         printf("Directory path: %s\n", directorypath); // 디렉토리 경로 출력
         fprintf(file, "<b> Directory path : %s</b><br>", directorypath); // HTML 파일에 디렉토리 경로 출력
         for (int i = 0; i < file_count; i++) // 디렉토리 내 모든 파일의 블록 수의 합을 계산
         {
            // 경로와 파일 이름을 합침
            strcpy(path, dirname);
            strcat(path, "/");
            strcat(path, filenames[i]);
            stat(path, &filestat);
            block += filestat.st_blocks; // st_blocks 멤버를 block 변수에 더해 디렉토리 내 모든 파일의 블록 수의 합을 구함
         }

         printf("total: %d\n", block / 2); // 파일의 블록 수 출력
         fprintf(file, "<b> total %d</b><br>", block / 2); // HTML 파일에 파일의 블록 수 출력
         fprintf(file, "<table border = \"1\">\n"); // HTML 파일에 테이블 태그 출력
         fprintf(file, "<tr><th>Name</th><th>Permission</th><th>Link</th><th>Owner</th><th>Group</th><th>Size</th><th>Last Modified</th></tr>\n"); // HTML 파일에 테이블 헤더 삽입
         for (int i = 0; i < file_count; i++)
         {
            print_file_info(hflag, dirname, filenames[i]); // 파일 정보 출력 함수 호출
         }
      }
      else // -l 옵션이 꺼져있을 경우
      {
         printf("Directory path: %s\n\n", directorypath); // 디렉토리 경로 출력
         fprintf(file, "<b> Directory path : %s</b>\n", directorypath); // HTML 파일에 디렉토리 경로 출력
         fprintf(file, "<table border= \"1\">/\n");  // HTML 파일에 테이블 태그 출력
         fprintf(file, "<tr><th>Name</th></tr>\n"); // HTML 파일에 파일 이름 컬럼 출력
         for (int i = 0; i < file_count; i++)
         {
            printf("%s\n", filenames[i]); // 파일이름 출력
            fprintf(file, "<tr><td>%s</td></tr></b>", filenames[i]); // HTML 파일에 파일 이름 출력
         }
      }
      closedir(dirp); // 디렉토리 닫기
      fprintf(file, "</table>\n"); // HTML 파일에 테이블 태그 닫기
   }
}

///////////////////////////////////////////////////////////////////////////////
// wildcardpattern					     	             //
// ========================================================================= //
// Description: This function checks for wildcard characters ('*' or '?') or //
//		character classes ('[]') in a given string. Returns 1 if the //
//		string has wildcard characters and 0 if no wildcard 	     //
//		characters.						     //
// Parameters:  str - String representing the file name			     //
///////////////////////////////////////////////////////////////////////////////
// 파일 이름에 와일드카드 문자가 있는지 검사하는 함수
int wildcardpattern(const char *str)
{
   if (strchr(str, '*') != NULL || strchr(str, '?') != NULL) // 문자열에 '*' 또는 '?' 문자가 있는지 검사
   {
      return 1; // 있으면 1 반환
   }

   for (int i = 0; str[i] != '\0'; i++) // 문자열에 '[]' 문자가 있는지 검사
   {
      if (str[i] == '[')
      {
         while (str[i] != '\0' && str[i] != ']') // '[' 다음에 ']' 문자가 나올 때까지 건너뜀
         {
            i++;
         }
         if (str[i] == '\0' || i == 1 || str[i - 1] != '[') // ']' 문자가 없거나 '[' 다음 문자가 바로 ']' 문자이면 와일드카드 문자가 아님
         {
            return 1;
         }
      }
   }
   return 0; // 와일드카드 문자가 없으면 0 반환
}

int main(int argc, char **argv)
{
   int aflag = 0, lflag = 0, hflag = 0, Sflag = 0, rflag = 0; // 각 옵션을 나타내는 플래그 변수
   int c = 0;
   char listfile1[1024][1024]; // 파일 이름 저장 배열
   char listfile2[1024][1024]; // 디렉토리 이름 저장 배열
   int file_count1 = 0;        // 파일 개수
   int file_count2 = 0;        // 디렉토리 개수
   char cwd[1024];
   file = fopen("html_ls.html", "w"); // html_ls.html 파일을 쓰기 모드로 열고 파일 포인터를 file 변수에 저장
   if (file == 0) // 파일을 열지 못했을 경우
   {
      printf("error\n");  //오류 메시지 출력
      return -1;
   }

   fprintf(file, "<html>\n"); // html 문서의 시작 태그
   fprintf(file, "<head>\n"); // html head 태그
   getcwd(cwd, sizeof(cwd)); // 현재 작업 디렉토리를 cwd 변수에 저장
   fprintf(file, "<title> %s </title>\n", cwd); // 타이틀 태그
   fprintf(file, "</head>\n"); // head 태그 닫기
   fprintf(file, "<body>\n"); // body 태그
   fprintf(file, "<h1>"); // h1 태그
   for (int i = 0; i < argc; i++)
   {
      fprintf(file, " %s", argv[i]); // 프로그램 실행 시 전달된 인자를 h1 태그 내에 출력
   }
   fprintf(file, "</h1><br>"); // h1 태그 닫기

   while ((c = getopt(argc, argv, "alhSr")) != -1) // 명령줄 옵션 parsing
   {
      switch (c)
      {
      case 'a': // a옵션일때
         aflag++;
         break;
      case 'l': // l옵션일때
         lflag++;
         break;
      case 'h': // h옵션일때
         hflag++;
         break;
      case 'S': // S옵션일때
         Sflag++;
         break;
      case 'r': // r옵션일때
         rflag++;
         break;
      case '?': // 알 수 없는 옵션이 들어왔을 때
         printf("unknown option character\n");
         break;
      }
   }

   if (argc == optind) // 인자가 없을 때
   {
      list_files(aflag, lflag, hflag, Sflag, rflag, "."); // 현재 디렉토리에 대한 파일 리스트 출력
   }
   else // 명령줄 인자가 있는 경우
   {
      struct stat filestat; // 파일의 상태 정보를 저장할 구조체
      for (int i = optind; i < argc; i++) // 인자로 주어진 파일들에 대해 반복
      {
         if (wildcardpattern(argv[i])) // 와일드카드 패턴이 있으면
         {
            glob_t wildcardmatch; // glob 함수에서 반환되는 파일 리스트를 저장할 구조체
            glob(argv[i], 0, NULL, &wildcardmatch); // glob 함수를 이용해 와일드카드 패턴에 해당하는 파일들의 리스트를 가져옴
            for (int i = 0; i < wildcardmatch.gl_pathc; i++) // 파일 리스트에 대해 반복
            {
               if (strcmp(wildcardmatch.gl_pathv[i], "html_ls.html") == 0) // 파일 이름이 "html_ls.html"과 일치하면
               {
                  continue; // 건너뛰고 다음 파일로 넘어감
               }
               stat(wildcardmatch.gl_pathv[i], &filestat); // 파일의 상태 정보를 가져옴
               if (S_ISDIR(filestat.st_mode)) // 가져온 파일이 디렉토리일 때
               {
                  strcpy(listfile2[file_count2++], wildcardmatch.gl_pathv[i]); // 디렉토리 이름을 디렉토리 이름 배열에 추가
               }
               else
               {
                  strcpy(listfile1[file_count1++], wildcardmatch.gl_pathv[i]); // 파일 이름을 파일 이름 배열에 추가
               }
            }
            globfree(&wildcardmatch); // glob 함수에서 할당된 메모리 해제
         }
         else // 와일드카드 패턴이 없을 때
         {
            if (stat(argv[i], &filestat) == -1) // 파일 정보를 얻는데 실패했을 때
            {
               printf("Cannot access %s: No such file or directory\n", argv[i]);
            }
            stat(argv[i], &filestat);
            if (S_ISDIR(filestat.st_mode)) // 현재 가져온 파일이 디렉토리인지 확인
            {
               strcpy(listfile2[file_count2++], argv[i]); // 디렉토리 이름 배열에 추가
            }
            else
            {
               strcpy(listfile1[file_count1++], argv[i]); // 파일 이름 배열에 추가
            }
         }
      }
   }
   sort(Sflag, rflag, NULL, listfile1, file_count1); // 파일 이름 정렬
   sort(Sflag, rflag, NULL, listfile2, file_count2); // 디렉토리 이름 정렬
   for (int i = 0; i < file_count1; i++)
   {
      list_files(aflag, lflag, hflag, Sflag, rflag, listfile1[i]); // flag에 따라 출력할 파일의 정보 결정
   }
   for (int i = 0; i < file_count2; i++)
   {
      list_files(aflag, lflag, hflag, Sflag, rflag, listfile2[i]); // flag에 따라 출력할 디렉토리의 정보 결정
   }
   fprintf(file, "</body>\n"); // body 태그 닫기
   fprintf(file, "</html>"); // html 태그 닫기
   fclose(file); // 파일 닫기
   return 0;
}
