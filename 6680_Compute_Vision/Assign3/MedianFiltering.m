% Assignment 3
% Riley Densley
% A01227345

function [filteredIm] = MedianFiltering(im,mask)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
[mRow, mCol] = size(mask);
[row, col] = size(im);

filteredIm = im;

if(mRow ~= mCol)
    fprintf("Mask is not a square!\n");
    return;
elseif(mod(mRow,2) == 0)
    fprintf("Mask dimensions must be odd numbers.\n");
    return
elseif (mask < 0)
    fprintf("Mask values are not all positive");
    return
end

for r = 1:row
    for c = 1:col
        maskTotal = [im(r,c)];
        for rM = -(floor(mRow/2)): floor(mRow/2)
            for cM = -(floor(mCol/2)):floor(mCol/2)
                for i = 1:mask(rM+ ceil(mRow/2), cM+ceil(mCol/2))
                    if(r+rM >= 1 && r + rM <= row && c + cM >= 1 && c + cM <= col)
                        maskTotal = [maskTotal, im(r+rM, c+cM)];
                    else
                        maskTotal = [maskTotal, 0];
                    end
                end
            end
        end
        filteredIm(r, c) = uint8(median(maskTotal));
    end
    
end


end

