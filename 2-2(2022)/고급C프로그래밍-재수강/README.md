# 고급 C 프로그래밍
#### 과제 및 프로젝트 구현 
##### Programming Language : C 
##### Development Tool: Visual Studio 2022
---
1.
- 포인터를 이용핸 두 값의 교환 프로그램
- 입력된 문자 거꾸로 출력
2.
- C포인터와 배열의 사용 예제
- 배열 원소 출력 및 평균 계산
3.
- 정적 변수와 포인터를 이용한 합 계산
- 포인터 연산을 활용한 배열 값 출력과 수정
- 천 단위 표시 출력 프로그램

#### Student Information Management Program
이 프로그램을 통해 이름, 학생 ID, 전화번호 등 학생 정보를 관리할 수 있다. 텍스트 파일('data.txt')을 사용하여 데이터를 로드하고 저장한다. 아래는 데이터 유무에 따른 사용 가능한 기능과 동작이다.

| **Function**            | **Description**                                                                                | **When Data Exists**                                                                                        | **When Data Does Not Exist**                                                             |
|-------------------------|------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------|
| **Data Load**            | Load the saved data from `data.txt` file into the program.                                    | ![image](https://github.com/user-attachments/assets/e46ce619-84fa-41fd-b8a1-7f81f5d21e7f)                   | ![image](https://github.com/user-attachments/assets/7b2f6bfb-dcc4-40e0-a6db-47076c371dde)|
| **Insert**               | Insert a new student's information (name, student ID, phone number) into the program.         | ![image](https://github.com/user-attachments/assets/631d96b1-f5ba-43c2-89e6-acad25858a21)                                                                                                              |
| **Delete**               | Remove a student's data by searching with their student ID.                                   | ![image](https://github.com/user-attachments/assets/8d6e089a-ec30-4265-8c11-b41333d38734)                   | ![image](https://github.com/user-attachments/assets/c24dc48a-44fe-4095-a959-1d4a713b546b)|
| **Search**               | Search for a student's data by student ID.                                                    | ![image](https://github.com/user-attachments/assets/4f88ddaf-0dfa-438d-a70e-633b88569434)                   | ![image](https://github.com/user-attachments/assets/09ff6f82-9742-448e-91b2-2c493da90f25)|
| **Print All**            | Print all stored student information.                                                         | ![image](https://github.com/user-attachments/assets/139fd6ba-026e-4716-810e-41ace71ca73a)                                                                                                              |
| **Data Save & Exit**     | Save all student data to `data.txt` before exiting the program.                               | ![image](https://github.com/user-attachments/assets/6240faad-4fb0-4ffe-a9d7-35282a0b7abd)                                                                                                              |

#### Program Flow

1. The program first attempts to load existing data from `data.txt`.
2. You can choose from the following actions:
   - **Insert**: Add a new student's information.
   - **Delete**: Remove a student's data by their student ID.
   - **Search**: Look up a student's data by their student ID.
   - **Print All**: Display all stored student information.
   - **Save & Exit**: Save all data to `data.txt` and exit the program.
3. If no data is available in `data.txt`, the program will begin with an empty data set.
