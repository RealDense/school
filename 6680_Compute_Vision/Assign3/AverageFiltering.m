% Assignment 3
% Riley Densley
% A01227345


function [filteredIm] = AverageFiltering(im, mask)
%UNTITLED2 Summary of this function goes here
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
elseif (round(sum(mask, 'all')) ~= 1.0)
    fprintf("Mask values do not sum to 1.\n");
    return;
elseif(not((mask == flip(mask))))
    fprintf("Mask is not symmetric around the center\n");
    return;
elseif(not((mask == flip(mask, 2))))
    fprintf("Mask is not symmetric around the center\n");
    return;
end


for r = 1:row
    for c = 1:col
        maskTotal = 0.0;
        for rM = -(floor(mRow/2)): floor(mRow/2)
            for cM = -(floor(mCol/2)):floor(mCol/2)
                if(r+rM >= 1 && r + rM <= row && c + cM >= 1 && c + cM <= col)
                    maskTotal = maskTotal + double(im(r+rM, c+cM)) * mask(rM+ ceil(mRow/2), cM+ceil(mCol/2));
                end
                
            end
        end
        filteredIm(r, c) = uint8(maskTotal);
    end
end


end

