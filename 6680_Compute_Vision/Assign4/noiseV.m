% Assignment 4
% Riley Densley
% A01227345

function [nV] = noiseV(H, V, D)
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here

subband = cat(3, V, H, D);

% size(nV)


nV = sqrt(median(abs(subband), 'all')/0.6745);

nV = zeros(size(H));
[row, col] = size(H);

for i = 1:row
    for j = 1:col
        nV(i,j) = sqrt(median(abs(subband(i,j,:)), 'all')/0.6745);
    end
end


%  size(nV)
end

