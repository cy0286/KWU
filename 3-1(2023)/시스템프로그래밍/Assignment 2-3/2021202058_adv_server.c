///////////////////////////////////////////////////////////////////////////////
// File Name : 2021202058_adv_server.c				    	     //
// Date :  2023/05/10			                                     //
// Os : Ubuntu 16.04 LTS 64bits 	    				     //
// Author : Song ChaeYoung                                		     //
// Student ID : 2021202058			                             //
// ------------------------------------------------------------------------- //
// Title : System Programming Assignment #2-3       			     //
// Description : Based on the past task, write a web server program that     //
//	supports multiple access and access control. Implement code that     //
//	allows multiple clients to access at the same time by performing     //
//	tasks after socket connection with the client in a new process. At   //
//	this time, whenever connecting and disconnecting from the client,    //
//	the information of the clients is output as follows, and the	     //
//	information of the client that was connected is outputted once every //
//	10 seconds. The total number of connections ("Number of requests(s)" //
//	maintains the cumulative value since the server program was run, and //
//	the connection history at the bottom ensures that only up to 10      //
//	recent records are output (sorted in the latest time order).	     //
///////////////////////////////////////////////////////////////////////////////
#define _GNU_SOURCE       // FNM_CASEFOLD옵션
#define MAX_PATH_LEN 1024 // 최대 경로 길이 상수
#define MAX_FILES 1000    // 디렉토리 내 최대 파일 개수
#define PORTNO 40000      // port number
#define URL_LEN 256       // 파일 URL의 최대 길이
#define BUFSIZE 500000    // 버퍼 크기

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

void sort(char *path, char filename[][1024], int file_count); // 파일 이름 정렬 함수
void print_file_info(char *filepath, char *filename);         // 파일 정보 출력 함수
void list_files(int aflag, int lflag, char *dirname);         // 디렉토리 내 파일 리스트 출력 함수
void handle_signal(int signal);
// 전역 변수
FILE *file;                     // 파일 포인터 가리키는 전역 변수 file
int socket_fd, client_fd;       // 서버 소켓과 클라이언트 소켓 가리키는 전역 변수
char url[URL_LEN];              // 다운로드할 파일의 URL 저장 문자열 배열
char temp_message[BUFSIZE];     // 임시 메시지 저장 문자열 배열
char response_header[BUFSIZE];  // 응답 헤더 저장 문자열 배열
char response_message[BUFSIZE]; // 응답 메시지 저장 문자열 배열
int nrequest = 0;
int trequest = 0;
struct sockaddr_in history[10];
int PID[10];
time_t TIME[10];

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
///////////////////////////////////////////////////////////////////////////////
// 디렉토리 내의 파일 목록을 출력하는 함수
void list_files(int aflag, int lflag, char *dirname)
{
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
//	two signals, SIGCHLD and SIGALRM. SIGCHLD is responsible for 	     //
//	processing child process termination events and SIGALRM is displaying//
//	connection history.	     	                     		     //
// Parameters:  signal - An integer representing the signal number received  //
//	by the signal handler function. It is used to determine which signal //
//	is being handled.						     //
///////////////////////////////////////////////////////////////////////////////
void handle_signal(int signal)
{
    int status;
    pid_t pid;

    if (signal == SIGCHLD) // SIGCHLD 시그널 핸들러
    {
        while ((pid = waitpid(-1, &status, WNOHANG)) > 0) // 자식 프로세스가 종료되면, 모든 종료된 자식 프로세스 처리
        {
            // do nothing
        }
    }
    if (signal == SIGALRM) // SIGALRM 시그널 핸들러
    {
        printf("========= Connection History ===================================\n"); // 연결 기록 출력
        printf("Number of request(s) : %d\n", trequest);
        printf("No.\tIP\t\tPID\tPORT\tTIME\n");
        int n = nrequest - 1; // 인덱스 n을 설정해 최근 연결 기록부터 출력
        int i = trequest;     // 인덱스 i를 설정해 trequest 부터 시작
        while (i > (trequest - nrequest))
        {
            printf("%d\t%s\t%d\t%d\t%s\t\n", i, inet_ntoa(history[n].sin_addr), PID[n], history[n].sin_port, ctime(&TIME[n])); // 연결 정보 출력
            i--;                                                                                                               // 인덱스 감소
            n--; 													       // 연결 기록의 이전 항목으로 이동
        }
        alarm(10); // 10초마다 SIGALRM 시그널 발생
    }
}

int main(int argc, char **argv)
{
    alarm(10);                              // 10초마다 SIGALRM 시그널 발생
    signal(SIGCHLD, (void *)handle_signal); // SIGCHLD 시그널 핸들러 handle_signal 함수로 등록
    signal(SIGALRM, (void *)handle_signal); // SIGALRM 시그널 핸들러 handle_signal 함수로 등록

    int aflag = 0, lflag = 0; // 각 옵션을 나타내는 플래그 변수
    int c = 0;
    char cwd[1024];                              // 현재 작업 디렉토리를 저장하는 배열
    struct sockaddr_in server_addr, client_addr; // 서버와 클라이언트의 주소 정보 저장 구조체
    int len, len_out;                            // 주소 정보 구조체의 길이 저장 변수
    int opt = 1;                                 // 파일 디스크립터 관련 옵션 설정 변수

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

    while (1)
    {
        struct in_addr inet_client_address; // 클라이언트 IP 주소 저장 변수
        char buf[BUFSIZE] =                 // 클라이언트로부터 받은 데이터 저장할 버퍼
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
            return 0;
        }

        char IPlist[BUFSIZE];                // IP 주소 목록을 저장할 배열
        int flag = 0;                        // 일치 여부 나타내는 플래그 변수
        file = fopen("accessible.usr", "r"); // "accessible.usr" 파일을 읽기 모드로 열기
        if (file == 0)                       // 파일을 열지 못했을 경우
        {
            printf("error\n"); // 오류 메시지 출력
            return -1;
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

        pid_t pid = fork(); // 새로운 자식 프로세스 생성
        if (pid == 0)       // 자식 프로세스일 때
        {
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
                exit(0);                                                      // 자식 프로세스 종료
            }
            puts("========= New Client ============");
            printf("IP : %s\nPort : %d\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
            puts("=================================");
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
            sprintf(temp_message, "</h1><br>");     // h1 태그 닫기
            strcat(response_message, temp_message); // 생성한 문자열을 추가
            list_files(aflag, lflag, cwd);          // 현재 작업 디렉토리의 파일 목록을 출력
            close(client_fd);                       // 클라이언트와의 연결 종료
            close(socket_fd);                       // 소켓 연결 종료
            puts("========= Disconnected Client ============");
            printf("IP : %s\nPort : %d\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
            puts("=================================");
            exit(0); // 자식 프로세스 종료
        }
        else // 부모 프로세스일 때
        {
            close(client_fd); // 클라이언트 소켓 종료

            if (flag == 0)
            {
                continue; // 다음 클라이언트 요청 처리를 위해 반복문의 처음으로 이동
            }
            if (nrequest == 10)
            {
                trequest++;                  // 전체 요청 수 증가
                for (int i = 1; i < 10; i++) // 가장 오래된 요청 기록 제거, 새로운 요청 정보 추가
                {
                    history[i - 1] = history[i];
                    PID[i - 1] = PID[i];
                    TIME[i - 1] = TIME[i];
                }

                history[nrequest - 1].sin_addr = client_addr.sin_addr;
                history[nrequest - 1].sin_port = client_addr.sin_port;
                PID[nrequest - 1] = pid;
                TIME[nrequest - 1] = time(NULL);
            }
            else
            {
                trequest++;                                        // 전체 요청 수 증가
                history[nrequest].sin_addr = client_addr.sin_addr; // 새로운 요청 정보를 추가
                history[nrequest].sin_port = client_addr.sin_port;
                PID[nrequest] = pid;
                TIME[nrequest] = time(NULL);
                nrequest++; // 현재 요청 수 증가
            }
        }
    }
    close(socket_fd); // 소켓 닫기
    return 0;
}
