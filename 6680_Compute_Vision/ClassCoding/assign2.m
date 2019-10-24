% Assignment 2
% Riley Densley
% A01227345

%Problem 1


pepperIm = imread('peppers.bmp');
figure;
imshow(pepperIm);
title('RGB Original Image');

fprintf('-------- Finish Solving Problem 1 --------\n')
pause;

%Problem 2

%change image to gray scale
pepperGrayIm = rgb2gray(pepperIm);

%get the size of the image
[row, col, channel] = size(pepperIm);

fprintf('-------- Finish Solving Problem 2 --------\n')
pause;