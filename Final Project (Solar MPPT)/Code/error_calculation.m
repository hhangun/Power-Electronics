clear; clc; close all
% Time	Pmax Vsa Isa Duty Verr Vref V10 V12
% column name
V1=readtable('1115_up.xlsx');

%% data converting to double
V1=table2array(V1);

%% 
time1=V1(:,1);
Pmax_V1=V1(:,7);
Isa_V1=V1(:,8);
Vsa_V1=V1(:,9);
Po_V1=Vsa_V1.*Isa_V1;

%% calculate sum error

sumE_V1=sum(Pmax_V1-Po_V1)

%% plot data in matlab(test)

plot(time1,Pmax_V1,'-',time1,Po_V1,'--')
title('Power generation of Solar module, date: 11M 15D')
xlabel('Time[s]')
ylabel('Power[W]')
legend('Measured Pmax', 'Estimated Pmax')
grid on
