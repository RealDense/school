%Riley Densley
%Assignment 1

function [blurredIm] = BlurImage(oriIm)

[row, col, channel] = size(oriIm);
blurredIm = oriIm;
%step through array in increments of 4
for r = 1:4:row
    for c = 1:4:col
        %make array size of number of channels
        avg = zeros(channel,1);
        for idxr = 0:3
            for idxc = 0:3
                for chn = 1:channel
                    %add up all the values in a 4x4 area
                    %on each channel
                    avg(chn,1) = avg(chn,1) + double(oriIm(r+idxr, c + idxc, chn));
                end
            end
        end
        
        avg = avg/16;
        for idxr = 0:3
            for idxc = 0:3
                for chn = 1:channel
                    %set averaged value to the 4x4 area
                    %on each channel
                    blurredIm(r + idxr, c + idxc, chn) = avg(chn,1);
                end
            end
        end
    end
end



