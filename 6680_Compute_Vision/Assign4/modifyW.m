% Assignment 4
% Riley Densley
% A01227345

function [H,V,D] = modifyW(H,V,D, threshold)
%UNTITLED8 Summary of this function goes here
%   Detailed explanation goes here

[row,col] = size(H);
subband = cat(3, H, V, D);
size(subband);

for i = 1:row
    for j = 1:col
        for k = 1:3
            thres = threshold(i,j);
            %fprintf('i = %i, j = %i, k = %i\n', i, j, k);
            c = subband(i,j, k);
            if c >= thres
                c = c - thres;
            elseif c <= -thres
                c = c + thres;
            else
                c = 0;
            end
            
            subband(i,j,k) = c;
        end
    end
end

H = subband(:,:,1);
V = subband(:,:,2);
D = subband(:,:,3);

end

