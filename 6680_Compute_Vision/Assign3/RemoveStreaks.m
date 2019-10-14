% Assignment 3
% Riley Densley
% A01227345

function [cleanIm] = RemoveStreaks(im)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

[row, col, channel] = size(im);

mask5x5 = ones(3);
mask3x3 = [1 2 1; 2 4 2; 1 2 1];
% medIm = MedianFiltering(im, mask3x3);
cleanIm = im;

% gxMask = [-1, -2, -1; 0, 0, 0; 1, 2, 1];
% gyMask = [-1, 0, 1; -2, 0, 2; -1, 0, 1];
% 
% gxTotal = conv2(im, gxMask, 'same');
% gyTotal = conv2(im, gyMask, 'same');
% 
% imGradF = (gxTotal.^2 + gyTotal.^2);
% tresh = 2*sqrt(mean(imGradF, 'all'));
% % 226.6821
% imEdge = sqrt(imGradF);
% imEdgeThresh = imEdge > tresh;
if(channel == 3)
    im = rgb2gray(im);
end

figure;
sgtitle("Removing Streaks");

subplot(1,2,1);
imshow(im);
title('Original Image');

subplot(1,2,2);
imshow(im>100);
title('Threshold Image');

% subplot(2,2,3);
% imshow(imEdgeThresh);
% title('Scaled Filtered Image');
% 
% subplot(2,2,4);
% imshow(uint8(~imEdgeThresh) .* im);
% title('Cleaned Image');
% truesize([220,220]);



end

