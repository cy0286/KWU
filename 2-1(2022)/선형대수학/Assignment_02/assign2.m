A=zeros(20,20); %데이터 요소 20개

t=0.01:0.01:0.2; %0.01 ~ 0.2
freq = 11:30; %주파수 11HZ ~ 30HZ

for i = 1:20 %person's hand
    for j= 1 : 20 %person's foot
        A(j,i) = cos(2*pi*freq(i)*t(j)); %흡수율 측정
    end
end

B=importdata('output.mat'); %측정된 신호 결과값

x=slv(A,B); %Homework 2 slv functions

disp(x); %출력함수
y=inv(A); %MATLAB 내장함수를 사용하여 결과비교를 함

z=y*B; %A를 inverse한 값에 B를 곱해줌
disp(z); %출력함수