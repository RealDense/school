% Assingment 2
% Riley Densley
% A01227345

function [histograms] = CalHist(image, norm, both)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

[row, col] = size(image);
histograms = zeros(1,256);
min(image, [], "all");
max(image, [], "all");
for r = 1:(row)
    for c = 1:(col)
    
        histograms(image(r, c)+1) = histograms(image(r,c)+1)+1;

    end
end

normHist = histograms/(row*col);
if norm
    histograms = normHist;
end
if both
    histograms = [histograms; normHist];
end
