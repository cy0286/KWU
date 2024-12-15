#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define MAX 200

typedef struct {//��ȣȭ �� ��ȣȭ �ڵ带 ������ ����ü
    char str[MAX];
}STRING;

enum CHOICE { ENCRYPT = 1, DEENCRYPT, DELETE_E, DELETE_D };//��ȣȭ,��ȣȭ �ڵ� ���� ������ �߰�

void SelectMenu(int*);//�޴����� �Լ�
void GetChangeAmount(int*);//
void ChangeString(STRING*, const int, const int, int*, int*, int);//��ȣȭ, ��ȣȭ ���� �Լ�(GetString�Լ��� ��ħ,��Ʈ�Լ��鵵 ��ħ)
int Delete(STRING*, const int, int*);//��ȣȭ,��ȣȭ �ڵ� ���� �Լ�
void PrintEncodeResult(STRING*, int*);//��ȣȭ ����Ʈ ��� �Լ�
void PrintDecodeResult(STRING*, int*);//��ȣȭ ����Ʈ ��� �Լ� 
int SaveEncodeFile(STRING*, int*);//��ȣȭ ������ �����Լ�
int SaveEncodeFile(STRING*, int*);//��ȣȭ ������ �����Լ�
int OpenEncodeFile(STRING*, int*);//��ȣȭ ������ �ҷ����� �Լ�
int OpenDecodeFile(STRING*, int*);//��ȣȭ ������ �ҷ����� �Լ�

int main(void)
{
    int choice, amount;
    STRING encode[MAX];//��ȣȭ �ڵ� ������ ����ü �迭
    STRING decode[MAX];//��ȣȭ �ڵ� ������ ����ü �迭
    int number1 = 0;//����� ��ȣȭ �ڵ��� ��
    int number2 = 0;//����� ��ȣȭ �ڵ��� ��

    OpenEncodeFile(encode, &number1);//����� ��ȣȭ ����Ʈ �ҷ�����
    OpenDecodeFile(decode, &number2);//����� ��ȣȭ ����Ʈ �ҷ�����

    int num = 10; //��Ʈ ���� ũ�⸦ 10���� ����
    long long int* arr;
    arr = (int*)malloc(sizeof(long long int) * num); //��Ʈ ���� ũ���� 10��ŭ �޸� �Ҵ�
    for (int i = 0; i < num; i++) {
        arr[i] = i + 1; //��Ʈ ���� 1���� 10������ ��ҷ� �ʱ�ȭ
    }


    while (1) {
        SelectMenu(&choice);

        if (choice == 1) {//��ȣȭ ����
            GetChangeAmount(&amount);
            ChangeString(encode, choice, amount, &number1, arr, num);

        }
        else if (choice == 2) {//��ȣȭ ����
            GetChangeAmount(&amount);
            ChangeString(decode, choice, amount, &number2, arr, num);

        }
        else if (choice == 3) {//��ȣȭ �ڵ� ����
            Delete(encode, choice, &number1);
        }
        else if (choice == 4) {//��ȣȭ �ڵ� ����
            Delete(decode, choice, &number2);
        }
        else if (choice == 5) {//��� ����Ʈ ���� ���
            PrintEncodeResult(encode, &number1);
            PrintDecodeResult(decode, &number2);
        }
        else if (choice == 6) {//��ȭ�� �����͸� ���� �����ϰ� ����
            SaveEncodeFile(encode, &number1);
            SaveDecodeFile(decode, &number2);
            free(arr);
            return 0;
        }
        else {//�޴� ��ȣ �Է� ����
            printf("�Է� ����\n\n");
        }
    }
    return 0;
}

void SelectMenu(int* cho)
{
    printf("----�޴� ����----\n");
    printf("1.��ȣȭ\n");
    printf("2.��ȣȭ\n");
    printf("3.��ȣȭ�ڵ� ����\n");
    printf("4.��ȣȭ�ڵ� ����\n");
    printf("5.��� ����Ʈ ���\n");
    printf("6.��� ����Ʈ ����\n");
    printf("\n�޴� ����: ");
    scanf("%d", cho);

}

void GetChangeAmount(int* amo)
{
    printf("\n��ȣŰ(��ȣŰ) �Է� : ");
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
        rn = rand() % (num2 - j) + j; //j���� num-1 ���̿� ������ ���� ����
        temp = arr[j];
        arr[j] = arr[rn];
        arr[rn] = temp;
        sprintf(s, "%d", arr[j]); //�迭 arr�� ���� ������ ���ڿ� �迭 s�� ���ʷ� �����ϰ� 
        strcat(salt, s); // salt�� �̾�ٿ� ��Ʈ�� ����
    }


    switch (cho)
    {
    case ENCRYPT:
        if (*num < MAX) {//��ȣȭ ����Ʈ�� ���� ���� ���� ��
            printf("���ڿ� �Է� : ");
            scanf("%s", str);
            for (i = 0; str[i] != '\0'; i++)
            {
                if (str[i] + (amo % 94) > '~')//���� ū ��ȣȭ(��ȣȭ)Ű ���ڿ����� �����ϵ��� (amo%94)�� ����
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
            strcat(str, "-");//��Ʈ �κ� ��ȣȭ�ڵ忡 �̾�ٿ��ش�
            strcat(str, salt); //��Ʈ �κ� ��ȣȭ�ڵ忡 �̾�ٿ��ش�
            printf("��ȣȭ ��� : %s\n\n", str);
            strcpy(ptr[*num].str, str);//��ȣȭ�� �ڵ� ����
            (*num)++;//����� �ڵ�� ����
        }
        else {//��ȣȭ ����Ʈ�� ���� ���� ��
            printf("��ȣȭ �ڵ� ������\n");
        }
        break;

    case DEENCRYPT:
        if (*num < MAX) {////��ȣȭ ����Ʈ�� ���� ���� ���� ��
            printf("���ڿ� �Է� : ");
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
            strcat(str, "-");//��Ʈ �κ� ��ȣȭ�ڵ忡 �̾�ٿ��ش�
            strcat(str, salt); //��Ʈ �κ� ��ȣȭ�ڵ忡 �̾�ٿ��ش�
            printf("��ȣȭ ��� : %s\n\n", str);
            strcpy(ptr[*num].str, str);//��ȣȭ�� �ڵ� ����
            (*num)++;//����� �ڵ�� ����
        }
        else {////��ȣȭ ����Ʈ�� ���� ���� ��
            printf("��ȣȭ �ڵ� ������\n");
        }

    }
}
int Delete(STRING* ptr, const int cho, int* num) {//���� �Լ�
    char str[MAX];
    int i, j;

    switch (cho)
    {
    case DELETE_E:
        //��ȣȭ �ڵ� �����Ͱ� �Ѱ��� ����������
        if (*num > 0) {
            printf("\n������ ��ȣȭ �ڵ�: ");
            scanf("%s", str);

            for (i = 0; i < MAX; i++) {
                //���ڿ��̹Ƿ� ���ϱ����� strcmp���
                if (strcmp(str, ptr[i].str) == 0) {//�ش� ��ȣȭ �ڵ带 ã���� ��

                    (*num)--;
                    printf("�����Ǿ����ϴ�\n\n");

                    //�����Ͱ� ���� ���� �ʾҴٸ�
                    if (i != MAX - 1) {
                        for (j = i; j < MAX; j++) {
                            //���ڿ��̹Ƿ� strcpy�� ����Ͽ� ������ ����
                            strcpy(ptr[j].str, ptr[j + 1].str);//��ĭ �� ������ �����ش�
                        }
                        //����ü �迭�� �������� NULL�� �ٲ�
                        *ptr[MAX - 1].str = NULL;
                    }

                    //�����Ͱ� ���� á�ٸ�
                    else {
                        //����ü �迭�� �������� NULL�� �ٲ�
                        *ptr[MAX - 1].str = NULL;
                    }
                    return 0;
                }
            }
            printf("�ش� ��ȣȭ �ڵ尡 �����ϴ�\n\n");//��ȣȭ ����Ʈ���� �������� ������
            return 0;
        }

        //����� ��ȣȭ �ڵ� �����Ͱ� ���ٸ�
        else {
            printf("����� ��ȣȭ �ڵ尡 �����ϴ�\n\n");
            return 0;
        }
        break;

    case DELETE_D:
        //��ȣȭ �ڵ� �����Ͱ� �Ѱ��� ����������
        if (*num > 0) {
            printf("\n������ ��ȣȭ �ڵ�: ");
            scanf("%s", str);

            for (i = 0; i < MAX; i++) {
                //���ڿ��̹Ƿ� ���ϱ����� strcmp���
                if (strcmp(str, ptr[i].str) == 0) {//�ش� ��ȣȭ �ڵ带 ã���� ��

                    (*num)--;
                    printf("�����Ǿ����ϴ�\n\n");

                    //�����Ͱ� ���� ���� �ʾҴٸ�
                    if (i != MAX - 1) {
                        for (j = i; j < MAX; j++) {
                            //���ڿ��̹Ƿ� strcpy�� ����Ͽ� ������ ����
                            strcpy(ptr[j].str, ptr[j + 1].str);
                        }
                        //����ü �迭�� �������� NULL�� �ٲ�
                        *ptr[MAX - 1].str = NULL;
                    }

                    //�����Ͱ� ���� á�ٸ�
                    else {
                        //����ü �迭�� �������� NULL�� �ٲ�
                        *ptr[MAX - 1].str = NULL;
                    }
                    return 0;
                }
            }
            printf("�ش� ��ȣȭ �ڵ尡 �����ϴ�\n\n");//��ȣȭ ����Ʈ���� �������� ������
            return 0;
        }

        //����� ��ȣȭ �ڵ� �����Ͱ� ���ٸ�
        else {
            printf("����� ��ȣȭ �ڵ尡 �����ϴ�\n\n");
            return 0;
        }
    }

}

void PrintEncodeResult(STRING* ptr, int* num)//��ȣȭ ����Ʈ ��� �Լ�
{
    int i = 0;
    printf("\n<��ȣȭ �ڵ�>\n");
    if (*num > 0) {//��ȣȭ �ڵ� �����Ͱ� �Ѱ��� ������
        for (i = 0; i < *num; i++) {
            printf("%s\n", ptr[i].str);
        }
        printf("\n");
    }
    else//�ƹ��͵� ���� ��
        printf("��ȣȭ �ڵ尡 �����ϴ� \n\n");

}

void PrintDecodeResult(STRING* ptr, int* num) {//��ȣȭ ����Ʈ ��� �Լ�
    int i = 0;
    printf("<��ȣȭ �ڵ�>\n");
    if (*num > 0) {//��ȣȭ �ڵ� �����Ͱ� �Ѱ��� ������
        for (i = 0; i < *num; i++) {
            printf("%s\n", ptr[i].str);
        }
        printf("\n");
    }
    else//�ƹ��͵� ���� ��
        printf("��ȣȭ �ڵ尡 �����ϴ� \n\n");
}


int SaveEncodeFile(STRING* ptr, int* num) {//��ȭ�� ��ȣȭ �ڵ� �����͸� ���Ͽ� �����ϴ� �Լ�

    if (*num >= 0) {//�������� ���� 0�� �̻��� ��
        int i, state;
        FILE* fp = fopen("EncodeList.txt", "wt");

        /* fopen�Լ��� �����߻��� NULL�� �����ϹǷ�
        ���� ���� �� �����߻��� ���α׷��� ���� */
        if (fp == NULL) {
            printf("File Open Error!\n");
            return 1;
        }

        //����ü �迭�� ����� �����͸� ���Ͽ� ����
        //�ٹٲ����� �����Ͽ� ����
        for (i = 0; i < *num; i++) {
            fprintf(fp, "%s", ptr[i].str);
            fputc('\n', fp);
        }

        /* fclose�Լ��� ����� ������ �߻��ϸ�
        0�� �ƴ� �ٸ����� �����ϹǷ� ������ ����� �ǴܵǸ�
        �ȳ��� ���α׷��� ���� */
        state = fclose(fp);
        if (state != 0) {
            printf("File Close Error!\n");
            return 1;
        }
        printf("\n��ȣȭ ������ ����Ϸ�\n");
        return 0;
    }
    else {
        printf("\n����\n");
        return 0;
    }
}

int SaveDecodeFile(STRING* ptr, int* num) {//��ȭ�� ��ȣȭ �ڵ� �����͸� ���Ͽ� �����ϴ� �Լ�
    if (*num >= 0) {//�������� ���� 0�� �̻��� ��
        int i, state;
        FILE* fp = fopen("DecodeList.txt", "wt");

        /* fopen�Լ��� �����߻��� NULL�� �����ϹǷ�
        ���� ���� �� �����߻��� ���α׷��� ���� */
        if (fp == NULL) {
            printf("File Open Error!\n");
            return 1;
        }

        //����ü �迭�� ����� �����͸� ���Ͽ� ����
        //�ٹٲ����� �����Ͽ� ����
        for (i = 0; i < *num; i++) {
            fprintf(fp, "%s", ptr[i].str);
            fputc('\n', fp);
        }

        /* fclose�Լ��� ����� ������ �߻��ϸ�
        0�� �ƴ� �ٸ����� �����ϹǷ� ������ ����� �ǴܵǸ�
        �ȳ��� ���α׷��� ���� */
        state = fclose(fp);
        if (state != 0) {
            printf("File Close Error!\n");
            return 1;
        }
        printf("��ȣȭ ������ ����Ϸ�\n");
        return 0;
    }

    else {
        printf("\n����\n");
        return 0;
    }
}


int OpenEncodeFile(STRING* ptr, int* num) {//��ȣȭ ����Ʈ ���Ϸκ��� �����͸� �ҷ����� �Լ�

    int state;
    FILE* fp = fopen("EncodeList.txt", "rt");

    if (fp == NULL) {//������ �������� ���� ��
        printf("������ �����ϴ�!!\n");
        return 1;
    }

    //���Ͽ� ����� �����͸� ����ü �迭�� ����
    while (1) {
        fscanf(fp, "%s", ptr[*num].str);
        if (feof(fp) != 0)
            break;
        (*num)++;
    }

    /* fclose�Լ��� ����� ������ �߻��ϸ�
    0�� �ƴ� �ٸ����� �����ϹǷ� ������ ����� �ǴܵǸ�
    �ȳ��� ���α׷��� ���� */
    state = fclose(fp);
    if (state != 0) {
        printf("File Close Error!\n\n");
        return 1;
    }
    printf("����� ��ȣȭ ����Ʈ�� �����Խ��ϴ�\n");
    return 0;


}

int OpenDecodeFile(STRING* ptr, int* num) {//��ȣȭ ����Ʈ ���Ϸκ��� �����͸� �ҷ����� �Լ�
    int state;
    FILE* fp = fopen("DecodeList.txt", "rt");

    if (fp == NULL) {//������ �������� ���� ��
        printf("������ �����ϴ�!!\n\n");
        return 1;
    }

    //���Ͽ� ����� �����͸� ����ü �迭�� ����
    while (1) {
        fscanf(fp, "%s", ptr[*num].str);
        if (feof(fp) != 0)
            break;
        (*num)++;
    }

    /* fclose�Լ��� ����� ������ �߻��ϸ�
    0�� �ƴ� �ٸ����� �����ϹǷ� ������ ����� �ǴܵǸ�
    �ȳ��� ���α׷��� ���� */
    state = fclose(fp);
    if (state != 0) {
        printf("File Close Error!\n\n");
        return 1;
    }
    printf("����� ��ȣȭ ����Ʈ�� �����Խ��ϴ�\n\n");
    return 0;
}