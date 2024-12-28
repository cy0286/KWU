# 고급 C 프로그래밍
#### 과제 및 프로젝트 구현 
##### Programming Language : C 
##### Development Tool: Visual Studio 2022
---
1.
- 포인터를 이용한 두 값의 교환 프로그램
- 입력된 문자 거꾸로 출력
2.
- C포인터와 배열의 사용 예제
- 배열 원소 출력 및 평균 계산
3.
- 정적 변수와 포인터를 이용한 합 계산
- 포인터 연산을 활용한 배열 값 출력과 수정
- 천 단위 표시 출력
4.
- 3행 7열 2차원 배열
- 전치 행렬
5.
- 배열에서 최대값을 찾고 포인터로 반환
- 실수에서 정수부와 실수부 분리하기
- 명령어 라인 인자 처리 및 출력 예제
6.
- 구조체 메모리 할당 실습 1~3
7.
- 학점 구하는 프로그램
- 문제 1을 활용한 확장
8.
- 학생 정보 입력 및 구조체 저장 후 출력
- 도형의 종류와 데이터를 받아 면적 구하기 
9.
- 코드분석 실습 1~2
- 링크드리스트 실습
10.
- 텍스트 파일 내용을 읽어 출력
- 코드분석 실습
11.
- 동적 배열 입력, 최대값 찾기 및 평균 계산
- 구조체와 파일 입출력을 이용한 학생 정보 저장

---
#### 암호화 및 복호화 코드 관리 시스템
이 프로그램은 사용자가 입력한 문자열을 암호화하거나 복호화하는 기능을 제공한다. 또한, 암호화 및 복호화된 코드들을 파일에 저장하거나 불러올 수 있다. 아래는 사용자가 사용 가능한 기능과 동작이다.

| **Function**         | **Description**        | **Usage Example**    |
|----------------------|------------------------|----------------------|
| **Encryption**        | Encrypts a string.     | <img src="https://github.com/user-attachments/assets/f8431e22-47f2-4dfd-b2bd-17d04741c33d" width="250" height="200"/> |
| **Decryption**        | Decrypts an encrypted string. | <img src="https://github.com/user-attachments/assets/7fd00dc3-1aaf-4605-bae6-04e8de5301cd" width="250" height="200"/> |
| **Delete encryption code** | Deletes saved encryption codes. | <img src="https://github.com/user-attachments/assets/9059f14d-1bdc-46ba-9734-73bd3832c5b4" width="250" height="200"/> |
| **Delete decryption code** | Deletes saved decryption codes. | <img src="https://github.com/user-attachments/assets/7540faa0-e65e-4556-8483-e026ca4d3631" width="250" height="200"/> |
| **Print all lists**   | Prints all stored encryption and decryption codes. | <img src="https://github.com/user-attachments/assets/f9acea86-d487-4c48-93da-77e83de14161" width="200" height="200"/> |
| **Save all lists**    | Saves the encryption and decryption codes to a file and exits the program. | <img src="https://github.com/user-attachments/assets/67b4da9a-44ff-404d-a6b1-25ad176c4c60" width="200" height="200"/> |


#### Program Flow
1. The program first attempts to load existing encryption and decryption data from `EncodeList.txt` and `DecodeList.txt`.
2. The user is presented with the following menu options:
   - **1. Encrypt**: Encrypt a string and store the encrypted result.
   - **2. Decrypt**: Decrypt an encrypted string and store the decrypted result.
   - **3. Delete Encryption Code**: Remove an encryption code.
   - **4. Delete Decryption Code**: Remove a decryption code.
   - **5. Print All**: Print all stored encryption and decryption codes.
   - **6. Save & Exit**: Save all data to text files and exit the program.
3. If no data is available in the files, the program starts with empty lists.
4. The program continues running until the user chooses to save and exit.
