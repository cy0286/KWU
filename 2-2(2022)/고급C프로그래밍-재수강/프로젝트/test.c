#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define MAX 200

typedef struct {//암호화 및 복호화 코드를 저장할 구조체
    char str[MAX];
}STRING;

enum CHOICE { ENCRYPT = 1, DEENCRYPT, DELETE_E, DELETE_D };//암호화,복호화 코드 삭제 열거형 추가

void SelectMenu(int*);//메뉴선택 함수
void GetChangeAmount(int*);//
void ChangeString(STRING*, const int, const int, int*, int*, int);//암호화, 복호화 실행 함수(GetString함수와 합침,솔트함수들도 합침)
int Delete(STRING*, const int, int*);//암호화,복호화 코드 삭제 함수
void PrintEncodeResult(STRING*, int*);//암호화 리스트 출력 함수
void PrintDecodeResult(STRING*, int*);//복호화 리스트 출력 함수 
int SaveEncodeFile(STRING*, int*);//암호화 데이터 저장함수
int SaveEncodeFile(STRING*, int*);//복호화 데이터 저장함수
int OpenEncodeFile(STRING*, int*);//암호화 데이터 불러오는 함수
int OpenDecodeFile(STRING*, int*);//복호화 데이터 불러오는 함수

int main(void)
{
    int choice, amount;
    STRING encode[MAX];//암호화 코드 저장할 구조체 배열
    STRING decode[MAX];//복호화 코드 저장할 구조체 배열
    int number1 = 0;//저장된 암호화 코드의 수
    int number2 = 0;//저장된 복호화 코드의 수

    OpenEncodeFile(encode, &number1);//저장된 암호화 리스트 불러오기
    OpenDecodeFile(decode, &number2);//저장된 복호화 리스트 불러오기

    int num = 10; //솔트 값의 크기를 10으로 설정
    long long int* arr;
    arr = (int*)malloc(sizeof(long long int) * num); //솔트 값의 크기인 10만큼 메모리 할당
    for (int i = 0; i < num; i++) {
        arr[i] = i + 1; //솔트 값을 1부터 10까지의 요소로 초기화
    }


    while (1) {
        SelectMenu(&choice);

        if (choice == 1) {//암호화 시행
            GetChangeAmount(&amount);
            ChangeString(encode, choice, amount, &number1, arr, num);

        }
        else if (choice == 2) {//복호화 시행
            GetChangeAmount(&amount);
            ChangeString(decode, choice, amount, &number2, arr, num);

        }
        else if (choice == 3) {//암호화 코드 삭제
            Delete(encode, choice, &number1);
        }
        else if (choice == 4) {//복호화 코드 삭제
            Delete(decode, choice, &number2);
        }
        else if (choice == 5) {//모든 리스트 정보 출력
            PrintEncodeResult(encode, &number1);
            PrintDecodeResult(decode, &number2);
        }
        else if (choice == 6) {//변화된 데이터를 각각 저장하고 종료
            SaveEncodeFile(encode, &number1);
            SaveDecodeFile(decode, &number2);
            free(arr);
            return 0;
        }
        else {//메뉴 번호 입력 오류
            printf("입력 오류\n\n");
        }
    }
    return 0;
}

void SelectMenu(int* cho)
{
    printf("----메뉴 선택----\n");
    printf("1.암호화\n");
    printf("2.복호화\n");
    printf("3.암호화코드 삭제\n");
    printf("4.복호화코드 삭제\n");
    printf("5.모든 리스트 출력\n");
    printf("6.모든 리스트 저장\n");
    printf("\n메뉴 선택: ");
    scanf("%d", cho);

}

void GetChangeAmount(int* amo)
{
    printf("\n암호키(복호키) 입력 : ");
    scanf("%d", amo);
}

void ChangeString(STRING* ptr, const int cho, const int amo, int* num, int* arr, int num2)
{
    int i;
    char str[MAX];

    srand(time(NULL));
    int temp;
    int rn;
    char s[MAX] = { '\0' };
    char salt[MAX] = { '\0' };
    for (int j = 0; j < num2 - 1; j++)
    {
        rn = rand() % (num2 - j) + j; //j부터 num-1 사이에 임의의 정수 생성
        temp = arr[j];
        arr[j] = arr[rn];
        arr[rn] = temp;
        sprintf(s, "%d", arr[j]); //배열 arr의 정수 값들을 문자열 배열 s에 차례로 저장하고 
        strcat(salt, s); // salt에 이어붙여 솔트값 생성
    }


    switch (cho)
    {
    case ENCRYPT:
        if (*num < MAX) {//암호화 리스트에 아직 공간 있을 때
            printf("문자열 입력 : ");
            scanf("%s", str);
            for (i = 0; str[i] != '\0'; i++)
            {
                if (str[i] + (amo % 94) > '~')//아주 큰 암호화(복호화)키 숫자에서도 가능하도록 (amo%94)로 변경
                {
                    int less = str[i] - '~';

                    str[i] = '!';
                    str[i] += less;
                    str[i] += (amo % 94) - 1;

                }
                else if (str[i] + (amo % 94) < '!') {
                    int plus = '!' - str[i];

                    str[i] = '~';
                    str[i] -= plus;
                    str[i] += (amo % 94) + 1;

                }
                else
                    str[i] += (amo % 94);

            }
            strcat(str, "-");//솔트 부분 암호화코드에 이어붙여준다
            strcat(str, salt); //솔트 부분 암호화코드에 이어붙여준다
            printf("암호화 결과 : %s\n\n", str);
            strcpy(ptr[*num].str, str);//암호화된 코드 저장
            (*num)++;//저장된 코드수 증가
        }
        else {//암호화 리스트에 공간 없을 때
            printf("암호화 코드 가득참\n");
        }
        break;

    case DEENCRYPT:
        if (*num < MAX) {////복호화 리스트에 아직 공간 있을 때
            printf("문자열 입력 : ");
            scanf("%s", str);
            for (i = 0; str[i] != '\0'; i++)
            {
                if (str[i] - (amo % 94) < '!')
                {
                    int plus = '!' - str[i];

                    str[i] = '~';
                    str[i] -= plus;
                    str[i] -= (amo % 94) - 1;
                }
                else if (str[i] - (amo % 94) > '~') {
                    int less = str[i] - '~';

                    str[i] = '!';
                    str[i] += less;
                    str[i] -= (amo % 94) + 1;
                }
                else
                    str[i] -= (amo % 94);
            }
            strcat(str, "-");//솔트 부분 복호화코드에 이어붙여준다
            strcat(str, salt); //솔트 부분 복호화코드에 이어붙여준다
            printf("복호화 결과 : %s\n\n", str);
            strcpy(ptr[*num].str, str);//복호화된 코드 저장
            (*num)++;//저장된 코드수 증가
        }
        else {////암호화 리스트에 공간 없을 때
            printf("복호화 코드 가득참\n");
        }

    }
}
int Delete(STRING* ptr, const int cho, int* num) {//삭제 함수
    char str[MAX];
    int i, j;

    switch (cho)
    {
    case DELETE_E:
        //암호화 코드 데이터가 한개라도 남아있으면
        if (*num > 0) {
            printf("\n삭제할 암호화 코드: ");
            scanf("%s", str);

            for (i = 0; i < MAX; i++) {
                //문자열이므로 비교하기위해 strcmp사용
                if (strcmp(str, ptr[i].str) == 0) {//해당 암호화 코드를 찾았을 때

                    (*num)--;
                    printf("삭제되었습니다\n\n");

                    //데이터가 가득 차지 않았다면
                    if (i != MAX - 1) {
                        for (j = i; j < MAX; j++) {
                            //문자열이므로 strcpy를 사용하여 데이터 복사
                            strcpy(ptr[j].str, ptr[j + 1].str);//한칸 씩 앞으로 땡겨준다
                        }
                        //구조체 배열의 마지막을 NULL로 바꿈
                        *ptr[MAX - 1].str = NULL;
                    }

                    //데이터가 가득 찼다면
                    else {
                        //구조체 배열의 마지막을 NULL로 바꿈
                        *ptr[MAX - 1].str = NULL;
                    }
                    return 0;
                }
            }
            printf("해당 암호화 코드가 없습니다\n\n");//암호화 리스트내에 존재하지 않으면
            return 0;
        }

        //저장된 암호화 코드 데이터가 없다면
        else {
            printf("저장된 암호화 코드가 없습니다\n\n");
            return 0;
        }
        break;

    case DELETE_D:
        //복호화 코드 데이터가 한개라도 남아있으면
        if (*num > 0) {
            printf("\n삭제할 복호화 코드: ");
            scanf("%s", str);

            for (i = 0; i < MAX; i++) {
                //문자열이므로 비교하기위해 strcmp사용
                if (strcmp(str, ptr[i].str) == 0) {//해당 복호화 코드를 찾았을 때

                    (*num)--;
                    printf("삭제되었습니다\n\n");

                    //데이터가 가득 차지 않았다면
                    if (i != MAX - 1) {
                        for (j = i; j < MAX; j++) {
                            //문자열이므로 strcpy를 사용하여 데이터 복사
                            strcpy(ptr[j].str, ptr[j + 1].str);
                        }
                        //구조체 배열의 마지막을 NULL로 바꿈
                        *ptr[MAX - 1].str = NULL;
                    }

                    //데이터가 가득 찼다면
                    else {
                        //구조체 배열의 마지막을 NULL로 바꿈
                        *ptr[MAX - 1].str = NULL;
                    }
                    return 0;
                }
            }
            printf("해당 복호화 코드가 없습니다\n\n");//복호화 리스트내에 존재하지 않으면
            return 0;
        }

        //저장된 복호화 코드 데이터가 없다면
        else {
            printf("저장된 복호화 코드가 없습니다\n\n");
            return 0;
        }
    }

}

void PrintEncodeResult(STRING* ptr, int* num)//암호화 리스트 출력 함수
{
    int i = 0;
    printf("\n<암호화 코드>\n");
    if (*num > 0) {//암호화 코드 데이터가 한개라도 있으면
        for (i = 0; i < *num; i++) {
            printf("%s\n", ptr[i].str);
        }
        printf("\n");
    }
    else//아무것도 없을 때
        printf("암호화 코드가 없습니다 \n\n");

}

void PrintDecodeResult(STRING* ptr, int* num) {//복호화 리스트 출력 함수
    int i = 0;
    printf("<복호화 코드>\n");
    if (*num > 0) {//복호화 코드 데이터가 한개라도 있으면
        for (i = 0; i < *num; i++) {
            printf("%s\n", ptr[i].str);
        }
        printf("\n");
    }
    else//아무것도 없을 때
        printf("복호화 코드가 없습니다 \n\n");
}


int SaveEncodeFile(STRING* ptr, int* num) {//변화된 암호화 코드 데이터를 파일에 저장하는 함수

    if (*num >= 0) {//데이터의 수가 0개 이상일 때
        int i, state;
        FILE* fp = fopen("EncodeList.txt", "wt");

        /* fopen함수는 오류발생시 NULL을 리턴하므로
        파일 개방 중 오류발생시 프로그램을 종료 */
        if (fp == NULL) {
            printf("File Open Error!\n");
            return 1;
        }

        //구조체 배열에 저장된 데이터를 파일에 저장
        //줄바꿈으로 구분하여 저장
        for (i = 0; i < *num; i++) {
            fprintf(fp, "%s", ptr[i].str);
            fputc('\n', fp);
        }

        /* fclose함수는 종료시 오류가 발생하면
        0이 아닌 다른값을 리턴하므로 비정상 종료로 판단되면
        안내후 프로그램을 종료 */
        state = fclose(fp);
        if (state != 0) {
            printf("File Close Error!\n");
            return 1;
        }
        printf("\n암호화 데이터 저장완료\n");
        return 0;
    }
    else {
        printf("\n종료\n");
        return 0;
    }
}

int SaveDecodeFile(STRING* ptr, int* num) {//변화된 복호화 코드 데이터를 파일에 저장하는 함수
    if (*num >= 0) {//데이터의 수가 0개 이상일 때
        int i, state;
        FILE* fp = fopen("DecodeList.txt", "wt");

        /* fopen함수는 오류발생시 NULL을 리턴하므로
        파일 개방 중 오류발생시 프로그램을 종료 */
        if (fp == NULL) {
            printf("File Open Error!\n");
            return 1;
        }

        //구조체 배열에 저장된 데이터를 파일에 저장
        //줄바꿈으로 구분하여 저장
        for (i = 0; i < *num; i++) {
            fprintf(fp, "%s", ptr[i].str);
            fputc('\n', fp);
        }

        /* fclose함수는 종료시 오류가 발생하면
        0이 아닌 다른값을 리턴하므로 비정상 종료로 판단되면
        안내후 프로그램을 종료 */
        state = fclose(fp);
        if (state != 0) {
            printf("File Close Error!\n");
            return 1;
        }
        printf("복호화 데이터 저장완료\n");
        return 0;
    }

    else {
        printf("\n종료\n");
        return 0;
    }
}


int OpenEncodeFile(STRING* ptr, int* num) {//암호화 리스트 파일로부터 데이터를 불러오는 함수

    int state;
    FILE* fp = fopen("EncodeList.txt", "rt");

    if (fp == NULL) {//파일이 존재하지 않을 때
        printf("파일이 없습니다!!\n");
        return 1;
    }

    //파일에 저장된 데이터를 구조체 배열에 저장
    while (1) {
        fscanf(fp, "%s", ptr[*num].str);
        if (feof(fp) != 0)
            break;
        (*num)++;
    }

    /* fclose함수는 종료시 오류가 발생하면
    0이 아닌 다른값을 리턴하므로 비정상 종료로 판단되면
    안내후 프로그램을 종료 */
    state = fclose(fp);
    if (state != 0) {
        printf("File Close Error!\n\n");
        return 1;
    }
    printf("저장된 암호화 리스트를 가져왔습니다\n");
    return 0;


}

int OpenDecodeFile(STRING* ptr, int* num) {//복호화 리스트 파일로부터 데이터를 불러오는 함수
    int state;
    FILE* fp = fopen("DecodeList.txt", "rt");

    if (fp == NULL) {//파일이 존재하지 않을 때
        printf("파일이 없습니다!!\n\n");
        return 1;
    }

    //파일에 저장된 데이터를 구조체 배열에 저장
    while (1) {
        fscanf(fp, "%s", ptr[*num].str);
        if (feof(fp) != 0)
            break;
        (*num)++;
    }

    /* fclose함수는 종료시 오류가 발생하면
    0이 아닌 다른값을 리턴하므로 비정상 종료로 판단되면
    안내후 프로그램을 종료 */
    state = fclose(fp);
    if (state != 0) {
        printf("File Close Error!\n\n");
        return 1;
    }
    printf("저장된 복호화 리스트를 가져왔습니다\n\n");
    return 0;
}