% Assingment 2
% Riley Densley
% A01227345

function [enhancedIm, transFunc] = HistEqualization(inputIm)
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here

[row, col] = size(inputIm);

%Step 1
hist = CalHist(inputIm, true, false);
%Step 2
cumulitive = zeros(1,256);
cumulitive(1) = hist(1);
for i = 2:256
    cumulitive(i) = cumulitive(i-1) + hist(i);
    
%Step 3
transFunc = cumulitive * 255;

enhancedIm = inputIm;
for r = 1:row
    for c = 1:col
        enhancedIm(r,c) = transFunc(inputIm(r,c)+1);
    end
end


end

