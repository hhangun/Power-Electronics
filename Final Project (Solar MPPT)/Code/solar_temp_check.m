clear; clc; close all
% Time	Pmax Vsa Isa Duty Verr Vref V10 V12
% column name
V1=readtable('2022_1115_temp.csv');

%% data converting to double
V1=table2array(V1);

%% 
time1=V1(:,1);
Pmax_V1=V1(:,2);
% Isa_V1=V1(:,3);
% Vsa_V1=V1(:,4);
% Po_V1=Vsa_V1.*Isa_V1;

%% calculate sum error

% sumE_V1=sum(Pmax_V1-Po_V1)

%% plot data in matlab(test)

plot(time1,Pmax_V1,'-')
title('2022Y 11M 15D Solar Temperature')
xlabel('Time[s]')
ylabel('Solar irradiance[W/m^3')
%legend('Measured Pmax', 'Estimated Pmax')
grid on
