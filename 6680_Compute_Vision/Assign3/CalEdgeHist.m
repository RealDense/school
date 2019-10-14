% Assignment 3
% Riley Densley
% A01227345

function [edgeHist] = CalEdgeHist(im,bin)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

[row, col] = size(im);

edgeHist = zeros(bin,1);

gx = [-1, -2, -1; 0, 0, 0; 1, 2, 1];
gy = [-1, 0, 1; -2, 0, 2; -1, 0, 1];

gxTotal = conv2(im, gx, 'same');
gyTotal = conv2(im, gy, 'same');

for r = 1:row
    for c = 1:col

        
        indx = (atan2d(gxTotal(r,c),gyTotal(r,c)));
        indx = indx + 180;
        indx = ceil(indx/(360/bin));
        
        edgeHist(indx) = edgeHist(indx) + 1;
    end
end



end

