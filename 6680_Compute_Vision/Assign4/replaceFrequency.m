% Assignment 4
% Riley Densley
% A01227345

function [outputIm] = replaceFrequency(inputIm, location)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

numFreq = size(location);
outputIm = inputIm;
for i = 1:numFreq
    x = location(i, 1);
    y = location(i, 2);
    outputIm(x,y) = (sum(inputIm(x-1:x+1, y-1:y+1), 'all')-inputIm(x,y))/8;
    
    
end

end

