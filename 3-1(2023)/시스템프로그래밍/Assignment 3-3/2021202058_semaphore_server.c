///////////////////////////////////////////////////////////////////////////////
// File Name : 2021202058_semaphore_server.c			     	     //
// Date :  2023/05/28			                                     //
// Os : Ubuntu 16.04 LTS 64bits 	    				     //
// Author : Song ChaeYoung                                		     //
// Student ID : 2021202058			                             //
// ------------------------------------------------------------------------- //
// Title : System Programming Assignment #3-3       			     //
// Description : Based on the previous task, write a program that manages    //
//	the process and records client access information in the 	     //
//	server_log.txt file. In this task, the log file is controlled using  //
//	semaphores to make it accessible to only one thread at a time. At    //
//	this time, do not record history in the log file.		     //
///////////////////////////////////////////////////////////////////////////////
#define _GNU_SOURCE             // FNM_CASEFOLD옵션
#define MAX_PATH_LEN 1024       // 최대 경로 길이 상수
#define MAX_FILES 1000          // 디렉토리 내 최대 파일 개수
#define PORTNO 40000            // port number
#define URL_LEN 256             // 파일 URL의 최대 길이
#define BUFSIZE 500000          // 버퍼 크기
#define SHARED_MEMORY_KEY 40000 // 공유메모리 Key
#define MEM_SIZE 1024           // 공유 메모리 크기

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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fnmatch.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>

struct httpdConf // conf 구조체 선언
{
   int maxChilds;    // 최대 자식 프로세스 개수
   int maxIdleNum;   // 최대 Idle 프로세스 개수
   int minIdleNum;   // 최소 Idle 프로세스 개수
   int startProcess; // 프로그램 시작 시 생성될 프로세스 개수
   int maxHistory;   // 출력되는 history의 수
} conf;

typedef struct sharedData // 공유 메모리 구조체 선언
{
   struct sockaddr_in history[10]; // 최근 10개의 연결 기록 저장
   pid_t PID[10];                  // 자식 프로세스의 PID 저장
   pid_t IPID[10];                 // Idle proecess PID
   time_t TIME[10];                // 시간 정보 저장
   int nrequest;                   // 현재까지의 요청 수 저장
   int trequest;                   // 전체 요청 수 저장
   int idleProcesses;              // 현재 Idle process의 수를 저장하는 변수
} SharedData;

typedef struct clientData // clent 구조체 선언
{
   struct sockaddr_in history2; // client 연결 기록 저장
   int CPID;                    // child 프로세스의 PID
   time_t TIME2;                // 시간 정보
} ClientData;

void initializeHttpdConf(struct httpdConf *conf, const char *filename); // httpd.conf 초기화
void sort(char *path, char filename[][1024], int file_count);           // 파일 이름 정렬 함수
void print_file_info(char *filepath, char *filename);                   // 파일 정보 출력 함수
void list_files(int aflag, int lflag, char *dirname, int client_fd);    // 디렉토리 내 파일 리스트 출력 함수
void handle_signal(int signal);                                         // 시그널(SIGCHLD, SIGALRM)에 대한 핸들러
pid_t child_make(int i, int socket_fd, int addrlen);                    // 자식 프로세스 생성 함수
void child_main(int i, int socket_fd, int addrlen);                     // 자식 프로세스의 메인 로직
void *shared_memory_initialize(void *vptr);                             // 공유 메모리 초기화하는 스레드 함수
void *shared_memory(void *vptr);                                        // 공유 메모리에 데이터를 저장하는 스레드 함수
void *shared_memory_print(void *vptr);                                  // 공유 메모리에 저장된 데이터를 출력하는 스레드 함수
void *log_write(void *vptr);                                            // 로그 파일에 작성하는 함수

// 전역 변수
char url[URL_LEN];                      // 다운로드할 파일의 URL 저장 문자열 배열
char temp_message[BUFSIZE];             // 임시 메시지 저장 문자열 배열
char response_header[BUFSIZE];          // 응답 헤더 저장 문자열 배열
char response_message[BUFSIZE];         // 응답 메시지 저장 문자열 배열
static pid_t *pids;                     // 자식 프로세스 PID 저장
static char *buf;                       // 데이터 저장 버퍼
int shm_id;                             // 공유 메모리 식별자 변수
int fd;                                 // 로그 파일 디스크립터 변수
sem_t *semaphore;                       // 세마포어 포인터 변수
const char *logfile = "server_log.txt"; // 로그 파일 경로를 나타내는 문자열 변수

pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

///////////////////////////////////////////////////////////////////////////////
// iniyislizeHttpConf				     			     //
// ========================================================================= //
// Description: Initializes the httpdConf structure, reads the settings from //
//	a given file, and assigns them to the structure's member variables.  //
//	are the same, compare and sort the strings converted to capital      //
//	letters. If rflag is true, sort the file name array in reverse order.//
// Parameters:  conf - The httpdConf structure pointer to be initialized.    //
//		filename - The name of the file from which to read the       //
//			settings.					     //
///////////////////////////////////////////////////////////////////////////////
// httpd.conf 초기화
void initializeHttpdConf(struct httpdConf *conf, const char *filename)
{
   FILE *file = fopen(filename, "r"); // 파일을 읽기 모드로 열기
   if (file == NULL)                  // 파일 열기 실패 시
   {
      printf("Unable to open file.\n"); // 오류 메시지 출력
      exit(1);                          // 프로그램 종료
   }

   char line[100];
   // 파일에서 한 줄 읽기
   if (fgets(line, 100, file) == NULL) // 파일이 비어있는 경우
   {
      printf("file is empty.\n"); // 오류 메시지 출력
      exit(1);                    // 프로그램 종료
   }

   memset(conf, 0, sizeof(struct httpdConf)); // httpdConf 구조체를 0으로 초기화
   while (fgets(line, 100, file) != NULL)
   {
      // 줄에서 키와 값을 분리
      char *key = strtok(line, ":");
      char *value = strtok(NULL, ":");

      if (key != NULL && value != NULL)
      {
         // 공백 및 개행 문자 제거
         key[strcspn(key, " \r\n")] = '\0';
         value += strspn(value, " \t");
         value[strcspn(value, " \r\n")] = '\0';

         // 키에 따라서 해당하는 멤버 변수에 값을 설정
         if (strcmp(key, "MaxChilds") == 0)
         {
            conf->maxChilds = atoi(value);
         }
         else if (strcmp(key, "MaxIdleNum") == 0)
         {
            conf->maxIdleNum = atoi(value);
         }
         else if (strcmp(key, "MinIdleNum") == 0)
         {
            conf->minIdleNum = atoi(value);
         }
         else if (strcmp(key, "StartProcess") == 0)
         {
            conf->startProcess = atoi(value);
         }
         else if (strcmp(key, "MaxHistory") == 0)
         {
            conf->maxHistory = atoi(value);
         }
      }
   }
   fclose(file); // 파일 닫기
}

///////////////////////////////////////////////////////////////////////////////
// sort					     			             //
// ========================================================================= //
// Description: Given an array of file names and its count, sorts the array  //
//	in ascending order based on file names. If the first character of a  //
//	file name is '.', it is treated as a hidden file. Use 		     //
//	case-insensitive selection sorting to sort.			     //
//	are the same, compare and sort the strings converted to capital      //
//	letters. If rflag is true, sort the file name array in reverse order.//
// Parameters: path - File path						     //
//	       filename - an array of file names to be sorted		     //
//	       file_count - the number of files in the array		     //
///////////////////////////////////////////////////////////////////////////////
// 파일 이름을 기준으로 선택 정렬하는 함수
void sort(char *path, char filename[][1024], int file_count)
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
         for (int k = 0; hidden_file1[k]; k++) // 대문자로 변환
         {
            hidden_file1[k] = toupper(hidden_file1[k]);
         }
         for (int k = 0; hidden_file2[k]; k++) // 대문자로 변환
         {
            hidden_file2[k] = toupper(hidden_file2[k]);
         }
         if (strcmp(hidden_file1, hidden_file2) > 0) // 대문자로 변환한 문자열 비교
         {
            strcpy(temp, filename[i]);
            strcpy(filename[i], filename[j]);
            strcpy(filename[j], temp);
         }
      }
   }
}

///////////////////////////////////////////////////////////////////////////////
// print_file_info					     	             //
// ========================================================================= //
// Description: This is a function that prints file information, such as     //
//	permission, owner, group, size, and modification time. The function  //
//	takes two arguments, the file path and the file name, and it uses the//
//	stat() function to read the file information. The function first     //
//	creates a file path by concatenating the file path and the file name,//
//	and then uses the lstat() function to read the file information. It  //
//	then creates a hyperlink to the file based on the URL provided.      //
// Parameters:  filpath - File path with file information to output	     //
//		filename - File name					     //
///////////////////////////////////////////////////////////////////////////////
// 파일 정보 출력 함수
void print_file_info(char *filepath, char *filename)
{
   struct stat filestat; // 파일의 정보를 읽어 구조체 변수 filestat에 저장
   struct passwd *pw;    // 파일의 소유자 정보를 저장할 구조체 변수
   struct group *gr;     // 파일의 그룹 정보를 저장할 구조체 변수

   char path[1024];     // 파일 경로 저장할 변수
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
   char hyperlink[1024];           // 파일의 하이퍼링크를 저장할 변수
   char temp[1024];                // url을 복사할 임시 변수
   strcpy(temp, url);              // url을 temp에 복사
   if (strcmp(filename, ".") == 0) // 만약 파일명이 .인 경우
   {
      strcpy(hyperlink, temp); // 현재 디렉토리를 가리키는 하이퍼링크 생성
   }
   else if (strcmp(filename, "..") == 0) // 만약 파일명이 ..인 경우
   {
      char *last_slash = strrchr(temp, '/'); // url에서 마지막 /를 찾음
      if (last_slash == temp)                // url에 /가 없는 경우
      {
         strcpy(hyperlink, "/"); // 루트 디렉토리를 가리키는 하이퍼링크 생성
      }
      else // url에 /가 있는 경우
      {
         strncpy(hyperlink, temp, last_slash - temp); // 마지막 / 앞까지의 문자열을 추출
         hyperlink[last_slash - temp] = '\0';         // 하이퍼링크 생성
      }
   }
   else
   {
      size_t url_len = strlen(temp); // url의 길이를 저장
      if (temp[url_len - 1] == '/')  // url이 /로 끝나는 경우
      {
         temp[url_len - 1] = '\0'; // /를 삭제
      }
      sprintf(hyperlink, "%s/%s", temp, filename); // 하이퍼링크 생성
   }

   // 파일 유형, 허가권, 링크 수, 소유자, 그룹, 파일 크기, 수정 시간 출력
   if (S_ISDIR(filestat.st_mode)) // 파일 유형이 디렉토리인 경우
   {
      permission[0] = 'd';
   }
   else if (S_ISLNK(filestat.st_mode)) // 파일 유형이 링크인 경우
   {
      permission[0] = 'l';
   }
   else // 그 외 경우 "-"로 표시
   {
      permission[0] = '-';
   }
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
   permission[10] = '\0';                                                     // 문자열 끝에 null 문자 추가
   // printf("%s\t", permission);                                                // 파일 허가권 정보 출력

   pw = getpwuid(filestat.st_uid); // uid에 대한 사용자 정보 구조체 가져오기
   gr = getgrgid(filestat.st_gid); // gid에 대한 그룹 정보 구조체 가져오기

   if (S_ISDIR(filestat.st_mode)) // 디렉토리인 경우
   {
      sprintf(temp_message, "<tr style = \"color: blue\">"); // 파란색으로 표시
      strcat(response_message, temp_message);                // 생성한 문자열을 추가
   }
   else if (S_ISLNK(filestat.st_mode)) // link 파일인 경우
   {
      sprintf(temp_message, "<tr style = \"color: green\">"); // 녹색으로 표시
      strcat(response_message, temp_message);                 // 생성한 문자열을 추가
   }
   else // 그 외 경우
   {
      sprintf(temp_message, "<tr style = \"color: red\">"); // 빨간색으로 표시
      strcat(response_message, temp_message);               // 생성한 문자열을 추가
   }

   sprintf(temp_message, "<td><a href = \"%s\">%s</a></td>\n", hyperlink, filename); // HTML table에 파일 이름 출력
   strcat(response_message, temp_message);                                           // 생성한 문자열을 추가
   sprintf(temp_message, "<td>%s</td>", permission);                                 // 파일 권한 출력
   strcat(response_message, temp_message);                                           // 생성한 문자열을 추가
   // printf("%4d\t  ", (int)filestat.st_nlink);                                        // 링크 수 출력
   // printf("%s\t", pw->pw_name);                                                      // 소유자 이름 출력
   // printf("%s\t", gr->gr_name);                                                      // 그룹 이름 출력
   sprintf(temp_message, "<td>%4d</td><td>%s</td><td>%s</td>", (int)filestat.st_nlink, pw->pw_name, gr->gr_name);
   strcat(response_message, temp_message); // 생성한 문자열을 추가
   // printf("%8lld\t", (long long)filestat.st_size);                       // 파일 크기 출력
   sprintf(temp_message, "<td>%8lld</td>", (long long)filestat.st_size); // 파일 크기 출력
   strcat(response_message, temp_message);                               // 생성한 문자열을 추가

   char *modtime = ctime(&filestat.st_mtime); // 수정 시간 문자열로 변환
   modtime[strlen(modtime) - 1] = '\0';       // 문자열 끝에 있는 개행 문자 제거
   // printf("%s  ", modtime);                            // 수정 시간 출력
   // printf("%s\n", filename);                           // 파일 경로 출력
   sprintf(temp_message, "<td>%s</td></tr>", modtime); // HTML table에 파일 수정 시간 출력
   strcat(response_message, temp_message);             // 생성한 문자열을 추가
}

///////////////////////////////////////////////////////////////////////////////
// list_files					     	             	     //
// ========================================================================= //
// Description: A function that outputs a list of files in an input 	     //
//		directory. It is divided into files and directories, and the //
//		file is printed according to the flag. The function also sets//
//		the appropriate content-type headers for the files being     //
//		served as part of a web server. If the file is an image, the //
//		header is set to "Content-type:image/*". If the file is an   //
//		HTML file, the header is set to "Content-type:text/html". For//
//		all other files, the header is set to 			     //
//		"Content-type:text/plain".	     	                     //
// Parameters:  aflag - Flag that determines whether hidden files are also   //
//			printed						     //
//		lflag - Flag that determines whether to output more 	     //
//			information					     //
//		dirname - Save the directory path to output		     //
//		client_fd - File descriptor used for client communication    //
///////////////////////////////////////////////////////////////////////////////
// 디렉토리 내의 파일 목록을 출력하는 함수
void list_files(int aflag, int lflag, char *dirname, int client_fd)
{
   FILE *file;
   DIR *dirp;                               // 디렉토리 포인터
   char directorypath[1024];                // 현재 경로 저장할 배열
   struct stat filestat;                    // 파일 정보 저장할 구조체
   char filenames[MAX_FILES][MAX_PATH_LEN]; // 파일 이름 저장할 배열 선언
   int file_count = 0;                      // 파일 개수 0으로 초기화
   struct dirent *dp;                       // 디렉토리 엔트리 구조체 포인터

   dirp = opendir(dirname);          // 디렉토리 열기
   realpath(dirname, directorypath); // 절대 경로로 변환하여 저장

   if (dirname != NULL && dirp == NULL) // 파일이면
   {
      file = fopen(dirname, "rb"); // 파일을 이진 모드로 열고, 파일 포인터를 file 변수에 저장
      if (file == 0)               // 파일을 열지 못했을 경우
      {
         printf("error\n"); // 오류 메시지 출력
         return;
      }

      fseek(file, 0, SEEK_END);    // 파일의 끝으로 이동
      long filesize = ftell(file); // 파일 크기 추출
      fseek(file, 0, SEEK_SET);    // 파일의 시작으로 이동

      // 파일 확장자에 따라 Content-type 설정
      if (fnmatch("*.jpg", dirname, FNM_CASEFOLD) == 0 ||
          fnmatch("*.png", dirname, FNM_CASEFOLD) == 0 ||
          fnmatch("*.jpeg", dirname, FNM_CASEFOLD) == 0)
      {
         // 이미지 컨텐츠 유형으로 응답 헤더 설정
         sprintf(response_header,
                 "HTTP/1.0 200 OK\r\n"
                 "Server:2019 simple web server\r\n"
                 "Content-length:%ld\r\n"
                 "Content-type:image/*\r\n\r\n",
                 filesize);
      }
      else if (fnmatch("*.html", dirname, FNM_CASEFOLD) == 0) // 파일 확장명이 .html인 경우
      {
         // HTML 컨텐츠 유형으로 응답 헤더 설정
         sprintf(response_header,
                 "HTTP/1.0 200 OK\r\n"
                 "Server:2019 simple web server\r\n"
                 "Content-length:%ld\r\n"
                 "Content-type:text/html\r\n\r\n",
                 filesize);
      }
      else
      {
         // 일반 텍스트 유형으로 응답 헤더 설정
         sprintf(response_header,
                 "HTTP/1.0 200 OK\r\n"
                 "Server:2019 simple web server\r\n"
                 "Content-length:%ld\r\n"
                 "Content-type:text/plain\r\n\r\n",
                 filesize);
      }
      write(client_fd, response_header, strlen(response_header)); // 클라이언트에게 response header를 전송
      char buf[BUFSIZE];
      long cursize = 0;           // 현재 전송된 파일 크기
      while (cursize != filesize) // 전송이 완료될 때까지 반복
      {
         long sizepiece = fread(buf, 1, BUFSIZE, file); // 파일을 BUFSIZE 만큼 읽음
         cursize += sizepiece;                          // 전송된 파일 크기를 업데이트
         write(client_fd, buf, sizepiece);              // 클라이언트에게 파일을 전송
      }
      fclose(file); /// 파일을 닫음
   }
   else // 디렉토리일 경우
   {
      if (aflag == 0) // -a 옵션이 꺼져있을 경우
      {
         while ((dp = readdir(dirp)) != NULL) // 디렉토리 내의 모든 파일을 순회
         {
            strcpy(filenames[file_count], dp->d_name); // 파일 이름을 배열에 저장
            if (filenames[file_count][0] == '.')       //"."과 ".."은 건너뜀
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
            strcpy(filenames[file_count], dp->d_name); // 파일 이름을 배열에 저장
            file_count++;                              // 파일 개수를 증가
         }
      }

      sort(dirname, filenames, file_count); // 파일 이름 정렬 함수 호출

      if (lflag != 0) // -l 옵션이 켜져있을 경우
      {
         int block = 0;   // 디렉토리 내 모든 파일의 블록 수의 합
         char path[1024]; // 경로와 파일 이름을 저장할 문자열

         // printf("Directory path: %s\n", directorypath);                           // 디렉토리 경로 출력
         sprintf(temp_message, "<b> Directory path : %s</b><br>", directorypath); // HTML 파일에 디렉토리 경로 출력
         strcat(response_message, temp_message);                                  // 생성한 문자열을 추가
         for (int i = 0; i < file_count; i++)                                     // 디렉토리 내 모든 파일의 블록 수의 합을 계산
         {
            // 경로와 파일 이름을 합침
            strcpy(path, dirname);
            strcat(path, "/");
            strcat(path, filenames[i]);
            stat(path, &filestat);
            block += filestat.st_blocks; // st_blocks 멤버를 block 변수에 더해 디렉토리 내 모든 파일의 블록 수의 합을 구함
         }

         // printf("total: %d\n", block / 2);                                                                                                                 // 파일의 블록 수 출력
         sprintf(temp_message, "<b> total %d</b><br>", block / 2);                                                                                         // HTML 파일에 파일의 블록 수 출력
         strcat(response_message, temp_message);                                                                                                           // 생성한 문자열을 추가
         sprintf(temp_message, "<table border = \"1\">\n");                                                                                                // HTML 파일에 테이블 태그 출력
         strcat(response_message, temp_message);                                                                                                           // 생성한 문자열을 추가
         sprintf(temp_message, "<tr><th>Name</th><th>Permission</th><th>Link</th><th>Owner</th><th>Group</th><th>Size</th><th>Last Modified</th></tr>\n"); // HTML 파일에 테이블 헤더 삽입
         strcat(response_message, temp_message);                                                                                                           // 생성한 문자열을 추가
         for (int i = 0; i < file_count; i++)
         {
            print_file_info(dirname, filenames[i]); // 파일 정보 출력 함수 호출
         }
      }
      sprintf(temp_message, "</table>\n");    // HTML 파일에 테이블 태그 닫기
      strcat(response_message, temp_message); // 생성한 문자열을 추가
      sprintf(temp_message, "</body>\n");     // body 태그 닫기
      strcat(response_message, temp_message); // 생성한 문자열을 추가
      sprintf(temp_message, "</html>");       // html 태그 닫기
      strcat(response_message, temp_message); // 생성한 문자열을 추가
      // HTTP response header 생성
      sprintf(response_header,
              "HTTP/1.0 200 OK\r\n"
              "Server:2019 simple web server\r\n"
              "Content-length:%lu\r\n"
              "Content-type:text/html\r\n\r\n",
              strlen(response_message));
      write(client_fd, response_header, strlen(response_header));   // 클라이언트에게 HTTP response header 보내기
      write(client_fd, response_message, strlen(response_message)); // 클라이언트에게 HTTP response message 보내기
   }
   closedir(dirp); // 디렉토리 닫기
}

///////////////////////////////////////////////////////////////////////////////
// handle_signal					     	             //
// ========================================================================= //
// Description: The handle_signal function is a signal handler that handles  //
//	signals, SIGCHLD, SIGALRM, SIGINT, SIGTERM. SIGCHLD is responsible   //
//	for processing child process termination events and SIGALRM is       //
//	displaying connection history. SIGINT is the signal generated when   //
//	Ctrl+C is pressed in the terminal, and it  signals the end of the    //
//	program. SIGTERM refers to a signal requesting the process to        //
//	terminate.							     //
// Parameters:  signal - An integer representing the signal number received  //
//	by the signal handler function. It is used to determine which signal //
//	is being handled.						     //
///////////////////////////////////////////////////////////////////////////////
// 시그널에 대한 핸들러
void handle_signal(int signal)
{
   int status;
   pid_t pid;
   pthread_t tid;

   if (signal == SIGCHLD) // SIGCHLD 시그널 핸들러
   {
      pthread_t logtid;                                 // 로그 작성을 위한 스레드 식별자 변수
      char logMessage[1024];                            // 로그 메시지를 저장할 문자열 배열
      while ((pid = waitpid(-1, &status, WNOHANG)) > 0) // 자식 프로세스가 종료되면, 모든 종료된 자식 프로세스 처리
      {
         time_t current_time;                                       // 현재 시간 저장 변수
         time(&current_time);                                       // 현재 시간 저장
         char *time_str = ctime(&current_time);                     // 변수의 값을 문자열로 변환하여 저장
         time_str[strcspn(time_str, "\n")] = '\0';                  // 개행 문자를 찾아 '\0'로 대체하여 제거
         printf("[%s] %d process is terminated.\n", time_str, pid); // 종료된 자식 프로세스 상태 출력

         sprintf(logMessage, "[%s] %d process is terminated.\n", time_str, pid);
      }
      pthread_create(&logtid, NULL, log_write, (void *)logMessage); // 로그 작성 스레드 생성
      pthread_join(logtid, NULL);                                   // 로그 작성 스레드 종료까지 대기
   }
   if (signal == SIGALRM) // SIGALRM 시그널 핸들러
   {
      printf("========= Connection History ===================================\n"); // 연결 기록 출력
      printf("No.\tIP\t\tPID\tPORT\tTIME\n");
      pthread_create(&tid, NULL, shared_memory_print, NULL); // 공유 메모리 출력 스레드 생성
      pthread_join(tid, NULL);                               // 스레드가 종료될 때까지 대기
      alarm(10);                                             // 10초마다 SIGALRM 시그널 발생
   }
   if (signal == SIGINT) // SIGINT 시그널 핸들러
   {
      alarm(0); // alarm 0으로 초기화
      printf("\n");

      pthread_t logtid; // 로그 작성을 위한 스레드 식별자 변수
      char logMessage[1024];
      char templogMessage[1024];
      sprintf(templogMessage, "^c\n"); // 종료 시그널 메시지를 저장
      strcat(logMessage, templogMessage);
      pthread_create(&logtid, NULL, log_write, (void *)logMessage); // 로그 작성 스레드 생성
      pthread_join(logtid, NULL);                                   // 로그 작성 스레드 종료까지 대기
      for (int i = conf.startProcess - 1; i >= 0; i--)
      {
         time_t current_time1;                       // 현재 시간 저장 변수
         time(&current_time1);                       // 현재 시간 저장
         char *time_str1 = ctime(&current_time1);    // 변수의 값을 문자열로 변환하여 저장
         time_str1[strcspn(time_str1, "\n")] = '\0'; // 개행 문자를 찾아 '\0'로 대체하여 제거
         kill(pids[i], SIGTERM);
         sleep(1);
      }
      time_t current_time;                              // 현재 시간 저장 변수
      time(&current_time);                              // 현재 시간 저장
      char *time_str = ctime(&current_time);            // 변수의 값을 문자열로 변환하여 저장
      time_str[strcspn(time_str, "\n")] = '\0';         // 개행 문자를 찾아 '\0'로 대체하여 제거
      printf("[%s] Server is terminated.\n", time_str); // 부모 프로세스 종료 출력

      char logMessage1[1024];
      char templogMessage1[1024];
      sprintf(templogMessage1, "[%s] Server is terminated.\n", time_str);
      strcat(logMessage1, templogMessage1);
      pthread_create(&logtid, NULL, log_write, (void *)logMessage1); // 로그 작성 스레드 생성
      pthread_join(logtid, NULL);                                    // 로그 작성 스레드 종료까지 대기

      shmctl(shm_id, IPC_RMID, NULL);        // 공유 메모리 제거
      pthread_mutex_destroy(&counter_mutex); // mutex 객체 파괴
      free(pids);                            // 동적 할당된 메모리 해제
      exit(0);                               // 프로그램 종료
   }
   if (signal == SIGTERM) // SIGTERM 시그널 핸들러
   {
      exit(0); // 프로그램 종료
   }
}

//////////////////////////////////////////////////////////////////////////////
// pid_t child_make					     	             //
// ========================================================================= //
// Description: Functions that create child processes			     //
// Parameters:  i - Index of child processes				     //
//		socket_fd - socket file descriptor		             //
//		addrlen - size of address structure			     //
///////////////////////////////////////////////////////////////////////////////
// 자식 프로세스 생성 함수
pid_t child_make(int i, int socket_fd, int addrlen)
{
   pid_t pid;
   pid = fork(); // 자식 프로세스를 생성

   if (pid > 0) // 부모 프로세스
   {
      return (pid); // 해당 PID 반환
   }
   if (pid == 0) // 자식 프로세스
   {
      child_main(i, socket_fd, addrlen); // child_main() 함수 호출 -> 클라이언트 연결 처리
   }
}

//////////////////////////////////////////////////////////////////////////////
// void child_main					     	             //
// ========================================================================= //
// Description: This function is the main function executed by the child     //
//	process, It handles the client connection and processes their        //
//	requests.	     	                     		     	     //
// Parameters:   i - Index of child processes				     //
//		socket_fd - socket file descriptor			     //
//		addrlen - size of address structure 			     //
///////////////////////////////////////////////////////////////////////////////
// 자식 프로세스의 메인 로직
void child_main(int i, int socket_fd, int addrlen)
{
   signal(SIGINT, SIG_IGN);        // SIGINT 시그널 무시
   signal(SIGTERM, handle_signal); // SIGTERM 시그널에 대한 핸들러 설정

   int len;                  // 데이터 길이 변수
   int flag = 0;             // 일치 여부 나타내는 플래그 변수
   int aflag = 0, lflag = 0; // 각 옵션을 나타내는 플래그 변수
   char cwd[1024];           // 현재 작업 디렉토리를 저장하는 배열

   char logMessage[1024]; // 로그 메시지를 저장할 문자열 배열
   char logMessage1[1024];
   char templogMessage[1024]; // 임시로 저장할 로그 메시지를 저장할 문자열 배열
   char templogMessage1[1024];
   pthread_t tid;    // 스레드 식별자 변수
   pthread_t logtid; // 로그 작성 스레드 식별자 변수

   time_t current_time;                      // 현재 시간 저장 변수
   time(&current_time);                      // 현재 시간 저장
   char *time_str = ctime(&current_time);    // 변수의 값을 문자열로 변환하여 저장
   time_str[strcspn(time_str, "\n")] = '\0'; // 개행 문자를 찾아 '\0'로 대체하여 제거
   printf("[%s] %d process is forked.\n", time_str, getpid());
   sprintf(templogMessage1, "[%s] %d process is forked.\n", time_str, getpid());
   strcat(logMessage1, templogMessage1);
   pthread_create(&logtid, NULL, log_write, (void *)logMessage1); // 로그 작성 스레드 생성하여 로그 메시지 전달
   pthread_join(logtid, NULL);                                    // 로그 작성 스레드 종료까지 대기

   while (1)
   {
      FILE *file;                         // 파일 포인터 가리키는 전역 변수 file
      int client_fd;                      // 클라이언트 통신에 사용되는 파일 디스크립터
      struct sockaddr_in client_addr;     // 서버와 클라이언트의 주소 정보 저장 구조체
      struct in_addr inet_client_address; // 클라이언트 IP 주소 저장 변수
      pid_t pid;                          // 프로세스 ID 저장 변수
      ClientData cmemory;

      char buf[BUFSIZE] = // 클라이언트로부터 받은 데이터 저장할 버퍼
          {
              0,
          };
      char tmp[BUFSIZE] = // 버퍼 복사본
          {
              0,
          };

      char method[20];                                                      // HTTP 요청 메서드 저장 변수
      char *tok = NULL;                                                     // HTTP 요청 메시지 토큰화할 포인터
      memset(response_header, 0, sizeof(response_header));                  // HTTP 응답 헤더 초기화
      memset(response_message, 0, sizeof(response_message));                // HTTP 응답 메시지 초기화
      len = sizeof(client_addr);                                            // 클라이언트의 소켓 주소 구조체 크기 저장
      client_fd = accept(socket_fd, (struct sockaddr *)&client_addr, &len); // 클라이언트로부터 연결 요청 받음
      if (client_fd < 0)                                                    // accept 실패
      {
         printf("Server : accept failed\n"); // 에러 메시지를 출력
         continue;
      }

      char IPlist[BUFSIZE];                // IP 주소 목록을 저장할 배열
      int flag = 0;                        // 일치 여부 나타내는 플래그 변수
      file = fopen("accessible.usr", "r"); // "accessible.usr" 파일을 읽기 모드로 열기
      if (file == 0)                       // 파일을 열지 못했을 경우
      {
         printf("error\n"); // 오류 메시지 출력
         continue;
      }

      while (fgets(IPlist, BUFSIZE, file)) // 파일에서 한 줄씩 읽어와 IP 주소 목록과 비교
      {
         IPlist[strcspn(IPlist, "\n")] = '\0';                         // 읽어온 줄의 개행 문자 제거
         if (fnmatch(IPlist, inet_ntoa(client_addr.sin_addr), 0) == 0) // fnmatch() 함수를 사용해 IP 주소 패턴 매칭 수행
         {
            flag = 1; // 일치하는 IP 주소를 찾으면 플래그 변수 1로 설정
            break;    // 반복문 종료
         }
      }
      fclose(file);
      read(client_fd, buf, BUFSIZE); // 클라이언트로부터 데이터를 읽어옴
      strcpy(tmp, buf);              // buf를 tmp에 복사
      tok = strtok(tmp, " ");        // 첫 번째 공백 전까지 문자열을 잘라서 첫 번째 토큰을 가져옴
      if (tok == NULL)               // 토큰이 없는 경우
      {
         continue;
      }
      strcpy(method, tok);            // 첫 번째 토큰 메서드
      memset(url, 0, sizeof(url));    // url 배열 초기화
      if (strcmp(method, "GET") == 0) // 메서드가 GET인 경우
      {
         tok = strtok(NULL, " "); // 두 번째 공백 전까지 문자열을 잘라서 두 번째 토큰을 가져옴
         strcpy(url, tok);        // 두 번째 토큰 url
      }
      if (flag == 0)
      {
         // 접근이 거부된 경우 응답 메시지 작성
         sprintf(response_message,
                 "<html><head><link rel='icon' href='data:,'><title>Access Denied</title></head><body>"
                 "<h1>Access denied!</h1>\n"
                 "<h2>Your IP : %s</h2>\n"
                 "<p>You have no permission to access this web server. <br>"
                 "HTTP 403.6 - Forbidden: IP address reject</p></body></html>",
                 inet_ntoa(client_addr.sin_addr));
         // 응답 헤더 작성
         sprintf(response_header,
                 "HTTP/1.1 403 FORBIDDEN\r\n"
                 "Server:2023 simple web server\r\n"
                 "Content-length:%lu\r\n"
                 "Content-type:text/html\r\n\r\n",
                 strlen(response_message));
         write(client_fd, response_header, strlen(response_header));   // 응답 헤더 전송
         write(client_fd, response_message, strlen(response_message)); // 응답 메시지 전송
         close(client_fd);                                             // 클라이언트 소켓 종료
         continue;                                                     // 다음 클라이언트 요청 처리 위해 반복문 처음으로 이동
      }

      struct stat st;           // 파일 정보를 담는 구조체
      getcwd(cwd, sizeof(cwd)); // 현재 작업 디렉토리를 cwd 변수에 저장
      strcat(cwd, url);         // 요청한 파일의 경로를 만듦
      if (stat(cwd, &st) == -1) // 파일이 없는 경우
      {
         // 404 Not Found 응답 메시지 작성
         sprintf(response_header,
                 "HTTP/1.0 404 Notfound\r\n"
                 "Server:2019 simple web server\r\n"
                 "Content-length:%lu\r\n"
                 "Content-type:text/html\r\n\r\n",
                 strlen(response_message));
         // 응답 헤더 작성
         sprintf(response_message,
                 "<html><head><title>%s</title></head><body><h1>Not Found</h1><p>The request URL %s was not found on this server<br>HTTP 404 - Not Found</p></body></html>", cwd, url);
         write(client_fd, response_header, strlen(response_header));   // 응답 헤더 전송
         write(client_fd, response_message, strlen(response_message)); // 응답 메시지 전송
         close(client_fd);                                             // 클라이언트 소켓 종료
         continue;                                                     // 다시 accept 대기로 돌아감
      }
      sprintf(temp_message, "<html>\n");                   // html 문서의 시작 태그
      strcat(response_message, temp_message);              // 생성한 문자열을 추가
      sprintf(temp_message, "<head>\n");                   // html head 태그
      strcat(response_message, temp_message);              // 생성한 문자열을 추가
      sprintf(temp_message, "<title> %s </title>\n", cwd); // 타이틀 태그
      strcat(response_message, temp_message);              // 생성한 문자열을 추가
      sprintf(temp_message, "</head>\n");                  // head 태그 닫기
      strcat(response_message, temp_message);              // 생성한 문자열을 추가
      sprintf(temp_message, "<body>\n");                   // body 태그
      strcat(response_message, temp_message);              // 생성한 문자열을 추가
      sprintf(temp_message, "<h1>");                       // h1 태그
      strcat(response_message, temp_message);              // 생성한 문자열을 추가

      char *requestPath = url;

      time_t current_time;
      time(&current_time);
      char *time_str = ctime(&current_time);
      time_str[strcspn(time_str, "\n")] = '\0';

      struct timespec startTime, endTime;

      sprintf(templogMessage, "========= New Client ============\nTIME : [%s]\nURL : %s\nIP : %s\nPort : %d\nPID : %d\n=================================\n", time_str, requestPath, inet_ntoa(client_addr.sin_addr), client_addr.sin_port, getpid());
      strcat(logMessage, templogMessage);
      puts("========= New Client ============");
      printf("TIME : [%s]\nURL : %s\nIP : %s\nPort : %d\nPID : %d\n", time_str, requestPath, inet_ntoa(client_addr.sin_addr), client_addr.sin_port, getpid());
      puts("=================================");
      clock_gettime(CLOCK_MONOTONIC, &startTime);

      if (strcmp(url, "/") == 0) // URL이 root path
      {
         aflag = 0;
         lflag = 1;
         sprintf(temp_message, "Welcome to System Programming Http"); // h1 태그
         strcat(response_message, temp_message);                      // 생성한 문자열을 추가
      }
      else // 하위 디렉토리
      {
         aflag = 1;
         lflag = 1;
         sprintf(temp_message, "System Programming Http"); // h1 태그
         strcat(response_message, temp_message);           // 생성한 문자열을 추가
      }

      cmemory.history2.sin_addr = client_addr.sin_addr; // 클라이언트의 IP 주소를 연결 기록에 저장
      cmemory.history2.sin_port = client_addr.sin_port; // 클라이언트의 포트 번호를 연결 기록에 저장
      cmemory.CPID = getpid();                          // 현재 프로세스의 PID를 연결 기록에 저장
      cmemory.TIME2 = time(NULL);                       // 현재 시간을 연결 기록에 저장

      sprintf(temp_message, "</h1><br>");       // h1 태그 닫기
      strcat(response_message, temp_message);   // 생성한 문자열을 추가
      list_files(aflag, lflag, cwd, client_fd); // 현재 작업 디렉토리의 파일 목록을 출력

      sleep(5);

      time_t current_time1;
      time(&current_time1);
      char *time_str1 = ctime(&current_time1);
      time_str1[strcspn(time_str1, "\n")] = '\0';

      clock_gettime(CLOCK_MONOTONIC, &endTime);
      long duration = (endTime.tv_sec - startTime.tv_sec) * 1000000 + (endTime.tv_nsec - startTime.tv_nsec) / 1000;
      duration -= 5000000;
      sprintf(templogMessage, "========= Disconnected Client ============\nTIME : [%s]\nURL : %s\nIP : %s\nPort : %d\nPID : %d\nCONNECTING TIME : %ld(us)\n=================================\n", time_str, requestPath, inet_ntoa(client_addr.sin_addr), client_addr.sin_port, getpid(), duration);
      strcat(logMessage, templogMessage);
      puts("========= Disconnected Client ============");
      printf("TIME : [%s]\nURL : %s\nIP : %s\nPort : %d\nPID : %d\nCONNECTING TIME : %ld(us)\n", time_str1, requestPath, inet_ntoa(client_addr.sin_addr), client_addr.sin_port, getpid(), duration);
      puts("=================================");

      pthread_create(&logtid, NULL, log_write, (void *)logMessage); // 로그 작성 스레드 생성하여 로그 메시지 전달
      pthread_join(logtid, NULL);                                   // 로그 작성 스레드 종료까지 대기

      pthread_create(&tid, NULL, shared_memory, &cmemory); // shared_memory 함수를 실행하는 thread를 생성
      pthread_join(tid, NULL);                             // thread가 종료될 때까지 대기
      close(client_fd);                                    // 클라이언트와 연결 종료
   }
}

///////////////////////////////////////////////////////////////////////////////
// shared_memory_initialize				   	             //
// ========================================================================= //
// Description: Initialize and set up shared memory. This function runs on   //
//	the thread, creates shared memory, connects to the current process,  //
//	and performs initialization operations.			     	     //
// Parameters:  vptr - factor passed to the thread			     //
///////////////////////////////////////////////////////////////////////////////
// 공유 메모리 초기화하는 스레드 함수
void *shared_memory_initialize(void *vptr)
{
   void *shm_addr = (void *)0; // 공유 메모리 주소를 저장할 포인터
   SharedData *smemory = NULL; // 공유 메모리 구조체 포인터

   if ((shm_id = shmget((key_t)SHARED_MEMORY_KEY, sizeof(SharedData), IPC_CREAT | 0666)) == -1) // 공유 메모리 생성
   {
      printf("shmget fail\n");
      pthread_exit(NULL); // thread 종료
   }
   if ((shm_addr = shmat(shm_id, (void *)0, 0)) == (void *)-1) // 공유 메모리를 현재 프로세스에 연결
   {
      printf("shmat fail\n");
      pthread_exit(NULL); // thread 종료
   }
   smemory = (SharedData *)shm_addr;       // 공유 메모리를 구조체 포인터에 할당
   memset(smemory, 0, sizeof(SharedData)); // 공유 메모리 초기화
   for (int i = 0; i < conf.maxChilds; i++)
   {
      pthread_mutex_lock(&counter_mutex);
      smemory->IPID[i] = 0; // 자식 프로세스 ID 초기화
      pthread_mutex_unlock(&counter_mutex);
   }
   pthread_exit(NULL); // thread 종료
}

///////////////////////////////////////////////////////////////////////////////
// shared_memory					   	             //
// ========================================================================= //
// Description: It is responsible for storing the client's request           //
//	information in shared memory. This function runs on a thread,        //
//	retrieves client data and stores it in shared memory.		     //
// Parameters:  vptr - factor passed to the thread			     //
///////////////////////////////////////////////////////////////////////////////
// 공유 메모리에 데이터를 저장하는 스레드 함수
void *shared_memory(void *vptr)
{
   int i, val;
   void *shm_addr = (void *)0;               // 공유 메모리 주소를 저장할 포인터
   SharedData *smemory = NULL;               // 공유 메모리 구조체 포인
   ClientData *cmemory = (ClientData *)vptr; // 클라이언트 데이터 구조체 포인터

   if ((shm_id = shmget((key_t)SHARED_MEMORY_KEY, 0, 0)) == -1) // 공유 메모리 생성
   {
      printf("shmget fail\n");
      pthread_exit(NULL); // thread 종료
   }
   if ((shm_addr = shmat(shm_id, (void *)0, 0)) == (void *)-1) // 공유 메모리를 현재 프로세스에 연결
   {
      printf("shmat fail\n");
      pthread_exit(NULL); // thread 종료
   }
   smemory = (SharedData *)shm_addr; // 공유 메모리를 구조체 포인터에 할당
   pthread_mutex_lock(&counter_mutex);
   val = smemory->nrequest;    // 현재 요청 수를 가져옴
   if (val >= conf.maxHistory) // 최대 요청 기록 수를 초과하는 경우
   {
      for (i = 1; i < conf.maxHistory; i++) // 기록을 한 칸씩 앞으로 당김
      {
         smemory->history[i - 1] = smemory->history[i];
         smemory->PID[i - 1] = smemory->PID[i];
         smemory->TIME[i - 1] = smemory->TIME[i];
      }
      // 새로운 요청 정보를 마지막 위치에 저장
      smemory->history[val - 1].sin_addr = cmemory->history2.sin_addr;
      smemory->history[val - 1].sin_port = cmemory->history2.sin_port;
      smemory->PID[val - 1] = cmemory->CPID;
      smemory->TIME[val - 1] = cmemory->TIME2;
   }
   else // 초과하지 않는 경우 새로운 요청 정보를 다음 위치에 저장
   {
      smemory->history[val].sin_addr = cmemory->history2.sin_addr;
      smemory->history[val].sin_port = cmemory->history2.sin_port;
      smemory->PID[val] = cmemory->CPID;
      smemory->TIME[val] = cmemory->TIME2;
      smemory->nrequest = val + 1; // 요청 수 증가
   }
   pthread_mutex_unlock(&counter_mutex); // lock 해제
   pthread_exit(NULL);                   // thread 종료
}

///////////////////////////////////////////////////////////////////////////////
// shared_memory_print					   	             //
// ========================================================================= //
// Description: The function is responsible for outputting request           //
//	information stored in shared memory. This function runs on a thread  //
//	and accesses and outputs request information stored in shared memory //
//	in reverse order.		     	      			     //
// Parameters:  vptr - factor passed to the thread			     //
///////////////////////////////////////////////////////////////////////////////
// 공유 메모리에 저장된 데이터를 출력하는 스레드 함수
void *shared_memory_print(void *vptr)
{
   void *shm_addr = (void *)0; // 공유 메모리 주소 저장할 포인터
   SharedData *smemory = NULL; // 공유 메모리 구조체 포인터

   if ((shm_id = shmget((key_t)SHARED_MEMORY_KEY, 0, 0)) == -1) // 공유 메모리 생성
   {
      printf("shmget fail\n");
      pthread_exit(NULL); // thread 종료
   }
   if ((shm_addr = shmat(shm_id, (void *)0, 0)) == (void *)-1) // 공유 메모리를 현재 프로세스에 연결
   {
      printf("shmat fail\n");
      pthread_exit(NULL); // thread 종료
   }
   smemory = (SharedData *)shm_addr; // 공유 메모리를 구조체 포인터에 할당
   int n = smemory->nrequest - 1;    // 공유 메모리에서 최신부터 역순으로 접근하기 위한 인덱스 변수
   int i = 1;                        // 요청 번호 변수 초기화
   while (i < smemory->nrequest + 1) // 공유 메모리에 저장된 요청 개수만큼 반복
   {
      printf("%d\t%s\t%d\t%d\t%s\n", i, inet_ntoa(smemory->history[n].sin_addr), smemory->PID[n], smemory->history[n].sin_port, ctime(&smemory->TIME[n]));
      i++; // 요청 번호 증가
      n--; // 인덱스 감소
   }
   pthread_exit(NULL); // thread 종료
}

///////////////////////////////////////////////////////////////////////////////
// log_write				   	           		     //
// ========================================================================= //
// Description: The function executed by a thread that records a string	     //
//	 in a log file     	      			     		     //
// Parameters:  vptr - Copy the string from inside the function into an array// 
//	of data as the string to be recorded.			   	     //
///////////////////////////////////////////////////////////////////////////////
// 로그 파일에 작성하는 함수
void *log_write(void *vptr)
{
   char data[1024];
   strncpy(data, (char *)vptr, 1024); // 전달받은 문자열을 data 배열에 복사

   semaphore = sem_open("semaphore", O_RDWR);  // 세마포어 열기
   sem_wait(semaphore); // 세마포어 대기
   fd = open(logfile, O_RDWR | O_APPEND); // 로그 파일 열기
   if (logfile == 0) // 파일을 열지 못했을 경우
   {
      return NULL;
   }
   write(fd, data, strlen(data)); // 데이터를 로그 파일에 기록
   close(fd);  // 파일 디스크립터 닫기
   sem_post(semaphore); // 세마포어를 증가시켜 다른 스레드가 접근할 수 있도록 함
   sem_close(semaphore); // 세마포어 닫기
   pthread_exit(NULL); // 스레드 종료
}

int main(int argc, char **argv)
{
   alarm(10);                              // 10초마다 SIGALRM 시그널 발생
   signal(SIGCHLD, (void *)handle_signal); // SIGCHLD 시그널 핸들러 handle_signal 함수로 등록
   signal(SIGALRM, (void *)handle_signal); // SIGALRM 시그널 핸들러 handle_signal 함수로 등록
   signal(SIGINT, (void *)handle_signal);  // SIGINT 시그널 핸들러 handle_signal 함수로 등록

   int socket_fd;
   struct sockaddr_in server_addr, client_addr; // 서버와 클라이언트의 주소 정보 저장 구조체
   int opt = 1;                                 // 파일 디스크립터 관련 옵션 설정 변수
   int addrlen;
   pthread_t tid;

   const char *filename = "httpd.conf"; // 설정 파일 이름

   // 소켓 생성 & 소켓 파일 디스크립터 반환 함수 호출
   if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
   {
      printf("Server : Can't open stream socket\n");
      return 0;
   }
   setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); // 소켓 옵션 설정

   // 서버 주소 정보를 초기화하고 설정
   memset(&server_addr, 0, sizeof(server_addr));
   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
   server_addr.sin_port = htons(PORTNO);

   if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) // 소켓 바인딩 실패
   {
      printf("Server : Can't bind local address\n");
   }
   listen(socket_fd, 5); // 클라이언트의 연결 요청 대기

   initializeHttpdConf(&conf, filename); // httpd.conf 파일 읽어와 설정 초기화

   pthread_create(&tid, NULL, shared_memory_initialize, NULL); // 공유 메모리 초기화 스레드 생성
   pthread_join(tid, NULL);                                    // 공유 메모리 초기화 스레드 종료 대기

   pthread_t log;    // 로그 작성 스레드 식별자 변수
   pthread_t logtid; // 로그 작성 스레드 식별자 변수
   char logMessage[1024];
   semaphore = sem_open("semaphore", O_CREAT | O_EXCL, 0700, 1); // 세마포어 생성 및 초기화
   sem_close(semaphore);                                         // 세마포어 닫기
   fd = open(logfile, O_CREAT | O_TRUNC | O_RDWR, 0666);         // 로그 파일 열기
   close(fd);                                                    // 로그 파일 닫기

   pids = (pid_t *)malloc(conf.maxChilds * sizeof(pid_t)); // 자식 프로세스 ID 저장할 배열 동적 할당
   addrlen = sizeof(client_addr);                          // 클라이언트 주소 구조체 크기 저장

   time_t current_time;                      // 현재 시간 저장 변수
   time(&current_time);                      // 현재 시간 저장
   char *time_str = ctime(&current_time);    // 변수의 값을 문자열로 변환하여 저장
   time_str[strcspn(time_str, "\n")] = '\0'; // 개행 문자를 찾아 '\0'로 대체하여 제거

   printf("[%s] Server is started\n", time_str);
   sprintf(logMessage, "[%s] Server is started\n", time_str);

   pthread_create(&logtid, NULL, log_write, (void *)logMessage); // 로그 작성 스레드 생성
   pthread_join(logtid, NULL);                                   // 로그 작성 스레드의 종료를 대기

   for (int i = 0; i < conf.startProcess; i++) // 최대 자식 프로세스 수만큼 반복
   {
      pids[i] = child_make(i, socket_fd, addrlen); // child_make 함수 호출 -> 자식 프로세스 생성 -> 자식 프로세스 ID를 저장
   }
   for (;;) // 무한루프
   {
      pause(); // 신호 받을 때까지 대기
   }
}
