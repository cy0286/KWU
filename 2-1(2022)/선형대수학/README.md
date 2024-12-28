# 선형대수학
#### 과제 코드 
##### Programming Language : MATLAB 
##### Development Tool: MATLAB IDE
---
1. 행렬과 벡터 연산
- 행렬 열 교환
- 홀수 번째 행 오름차순 정렬
- 대각선 항목에 1 추가
- 내적 계산
- 벡터 샘플링
- 벡터 내적
- 벡터 결합
- 벡터 내적을 이용한 행렬 생성
- 행렬 원소별 거듭제곱
  
2. INVERSE PROBLEM을 통한 사람 신체의 주파수 흡수율 추정
- 주어진 20개의 사인파 신호를 사람의 신체 일부(손)에 입력하고, 다른 신체 부위(발)에서 측정된 복합 신호를 통해 신체의 흡수율(absorption rates) 계산
- linear inverse problem을 사용해 흡수율을 계산하고 MATLAB 내장 함수 inv() 함수와 결과 비교 
- slu.m : 행렬 AAA에 대해 부분 pivoting을 포함한 LU 분해를 수행해 PPP, LLL, UUU 행렬을 반환하는 코드
- slv.m : slu.m에서 계산된 PPP, LLL, UUU를 사용해 선형 방정식을 푸는 코드
  * P 행렬 : Permutation Matrix
  * L 행렬 : Lower Triangular Matrix
  * U 행렬 : Upper Triangular Matrix
