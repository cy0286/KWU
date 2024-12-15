%script
% #1 행렬의 열별 교환을 통해 첫번째 열과 마지막 열을 교환해줌
% #2 행렬 A의 홀수행을 오름차순으로 정리해줌
% #3 행렬의 모든 대각선 항에 1을 추가해줌
% #4 3중첩 for문을 사용하여 행렬의 내부 곱을 계산해줌
% #5 sampling해서 벡터b로 부터 새로운 벡터 u를 생성해줌
% #6 행렬 A와 u의 내적 곱을 통해 새로운 벡터 t를 생성함
% #7 벡터 u와 t를 연결하여 m*2 형태의 행렬 C를 만들어줌
% #8 벡터 t와 u의 내부곱을 이용해 m*m 형태의 행렬 D를 만들어줌
% #9 행렬 B와 D 사이의 element-wise power를 계산하여 행렬 E에 넣어줌

% 1번
disp('#1번');

A = [1, 2, 3; 1, 2, 3; 1, 2, 3];
[N,N] = size(A);

B = A;
B(:,[1 end])=B(:,[end 1]);

disp(A);
disp(B);


% 2번
disp('#2번');

for i = 1:2:N
    A(i,:) = sort(A(i,:), "ascend");
end
fprintf("Sorted A \n");
disp(A);

% 3번
disp('#3번');

result = A+eye(N,N) ; 
disp(result)

% 4번\
disp('#4번');

[c,d]=size(B);
C=zeros(N,d);
for i = 1 : N
    for j = 1 : d
        n=0;
        for k = 1 : N
            n = n + A(i,k)*B(k,j);
        end
        C(i,j) = n;
    end
end

disp(C);


% 5번
disp('#5번');

b = [1,2,3,4,5];
[n,m]=size(b);
u = ones(N,1);

bla=randi(N,N,1);
if n>1
    for k=1:N
        u(k,1)=b(bla(k,1),1);
    end

elseif m>1
    for k=1:N
        u(k,1)=b(1,bla(k,1));
    end
end
disp(u);

% 6번
disp('#6번');

[N,n] = size(u);
t = zeros(N,1);
for i = 1:1:N
   for j = 1:1:1
       t(i,j)=0;
        for k = 1:1:N
            t(i,j)=t(i,j)+A(i,k)*u(k,j);
        end
    end
end    

disp(t);


% 7번
disp('#7번');

newVector = [t u];

disp(newVector);


% 8번 
disp('#8번');

S = u.';

D=zeros(N,N);

for i = 1 : N
    for j = 1 : N
        n=0;
        for k = 1
            n = n + t(i,k)*S(k,j);
        end
        D(i,j) = n;
    end
end

disp(D);


% 9번 
disp('#9번');

disp(B);
disp(D);

E = B.^D;

disp(E);