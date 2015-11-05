% estimate MSE of a clustered data
%
% author: saptarshi.das@shell.com

clear all; close all;

% Input filenames
cFName = 'Vertigo_phase2.csv';		% cluster file name
dFName = 'HiPC2015_IntelData_40k.csv';	% Input Dataset

% read data, we will read each record in a column. This will speed
% up processing as MATLAB stores data in column major format.
data = csvread(dFName)';
clus = csvread(cFName);
%clus=clus';
[M, N] = size(data);

if N ~= size(clus, 2)
  error('dimension missmatch');
end

NSam = N;
samp = randi(N, NSam, 1);

% find unique clusters
clusIdx = unique(clus);
NClus   = length(clusIdx);

% if indices begin with 0 increment all by one
if (clusIdx(1)==0)
  clusIdx = clusIdx + 1;
  clus    = clus + 1;
endif

% Allocate space for cluster centroid
cent     = zeros(M, NClus);
clusSize = zeros(NClus, 1);

% find centroid just by avaraging over each class
for i = 1 : NSam 
  iClus = clus(i);
  cent(:, iClus)  = cent(:, iClus) + data(:, i); 
  clusSize(iClus) = clusSize(iClus) + 1;
end
cent = cent * diag(1 ./ clusSize);

% find MSE 
mse = 0; 
for i = 1 : NSam
  iClus = clus(i);
  diffV = data(:, i) - cent(:, iClus);
  mse = mse + sumsq(diffV);
end

mse = mse / NSam;

