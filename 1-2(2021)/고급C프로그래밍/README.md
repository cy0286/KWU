# 고급 C 프로그래밍
#### 과제 및 프로젝트 구현 
##### Programming Language : C 
##### Development Tool: Visual Studio 2022
---
1.
- 포인터를 이용핸 배열 순서 반전
- 포인터를 이용한 배열 회전 이동
- 홀수와 짝수 구분
- 행렬 전치
- 포인터와 주소 반환을 이용한 덧셈 구현
2.
- 학생 점수 관리 및 평균 계산
- 구조체를 이용한 시간 형식 변환
- 구조체를 이용한 삼각형 유형 구분
- 열거형을 이용한 수업 수업료 계산
3.
- 알파벳 빈도 계산기
- 사전 순서 단어 정렬
- 문자열 대소문자 변환 및 개수 계산
4.
- 구구단 파일 생성 및 저장
- 학생 총점 파일 생성
- 성적 계산 및 파일 출력
5.
- 학생 정보 관리 프로그램 프로젝트

## Student Information Management Program
이 프로그램을 통해 이름, 학생 ID, 전화번호 등 학생 정보를 관리할 수 있다. 텍스트 파일('data.txt')을 사용하여 데이터를 로드하고 저장한다. 아래는 데이터 유무에 따른 사용 가능한 기능과 동작이다.

| **Function**            | **Description**                                                                                | **When Data Exists**                                                                                        | **When Data Does Not Exist**                                                             |
|-------------------------|------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------|
| **Data Load**            | Load the saved data from `data.txt` file into the program.                                    | ![image](https://github.com/user-attachments/assets/e46ce619-84fa-41fd-b8a1-7f81f5d21e7f)                   | ![image](https://github.com/user-attachments/assets/7b2f6bfb-dcc4-40e0-a6db-47076c371dde)|
| **Insert**               | Insert a new student's information (name, student ID, phone number) into the program.         | ![image](https://github.com/user-attachments/assets/631d96b1-f5ba-43c2-89e6-acad25858a21)                                                                                                              |
| **Delete**               | Remove a student's data by searching with their student ID.                                   | ![image](https://github.com/user-attachments/assets/8d6e089a-ec30-4265-8c11-b41333d38734)                   | ![image](https://github.com/user-attachments/assets/c24dc48a-44fe-4095-a959-1d4a713b546b)|
| **Search**               | Search for a student's data by student ID.                                                    | ![image](https://github.com/user-attachments/assets/4f88ddaf-0dfa-438d-a70e-633b88569434)                   | ![image](https://github.com/user-attachments/assets/09ff6f82-9742-448e-91b2-2c493da90f25)|
| **Print All**            | Print all stored student information.                                                         | ![image](https://github.com/user-attachments/assets/139fd6ba-026e-4716-810e-41ace71ca73a)                                                                                                              |
| **Data Save & Exit**     | Save all student data to `data.txt` before exiting the program.                               | ![image](https://github.com/user-attachments/assets/6240faad-4fb0-4ffe-a9d7-35282a0b7abd)                                                                                                              |

### Program Flow

1. The program first attempts to load existing data from `data.txt`.
2. You can choose from the following actions:
   - **Insert**: Add a new student's information.
   - **Delete**: Remove a student's data by their student ID.
   - **Search**: Look up a student's data by their student ID.
   - **Print All**: Display all stored student information.
   - **Save & Exit**: Save all data to `data.txt` and exit the program.
3. If no data is available in `data.txt`, the program will begin with an empty data set.
