% Assignment 4
% Riley Densley
% A01227345

function [topFreq] = chooseMag(inputIm)
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here


mag = sqrt((real(inputIm).^2) + (imag(inputIm).^2));

sortedMag = sort(unique(mag(:)),'descend');
topMag = sortedMag(2:9);
[row,col] = find(ismember(mag, topMag));
topFreq = [row,col];
end

