%Riley Densley
%Assignment 1

function [maxValue, minValue, meanValue, medianValue] = FindInfo(oriIm);
%set the max and min value to the first value in the original image
maxValue = oriIm(1,1);
minValue = oriIm(1,1);

[row, col] = size(oriIm);

%create an array of size equal to possible values in the original image
% 0 to 254 -- 255 values
aMedianCount = zeros(256);
meanValue = 0;
for r = 1:row
    
    for c = 1:col
        if(oriIm(r, c) > maxValue)
            maxValue = oriIm(r, c);
        end
        if(oriIm(r, c) < minValue)
            minValue = oriIm(r, c);
        end
        %plus one because arrays start at 1 and there is a 0 value
        aMedianCount(oriIm(r,c) + 1) = aMedianCount(oriIm(r,c) + 1) + 1;
        %convert value to double so it will grow greater than 255
        meanValue = meanValue + double(oriIm(r,c));
    end
end

count = 0;
for indx = 1:length(aMedianCount)
    
    count = count + aMedianCount(indx);
    
    if(count > (row*col)/2)
        %breaks once count is greater than half of the number of values in
        %the original image
        medianValue = indx - 1; %because arrays start at 1
        break;
    end
    
end


meanValue = meanValue/(row*col);


end
