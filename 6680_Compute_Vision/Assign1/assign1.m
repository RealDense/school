%Riley Densley
%Assignment 1

% Problem 1

%read in image and display it
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

%Transpose image
pepperGrayImT = pepperGrayIm';
%switch the top half with the bottom half
pepperGrayImH = [pepperGrayIm(row/2+1:row, 1:col); pepperGrayIm(1:row/2, 1:col)];
%mirror flip the image from left to right
pepperGrayImF = fliplr(pepperGrayIm);

%display all images in one figure
figure;

subplot(2,2,1);
imshow(pepperGrayIm)
title('pepperGrayIm')

subplot(2,2,2);
imshow(pepperGrayImT)
title('pepperGrayImT')

subplot(2,2,3);
imshow(pepperGrayImH)
title('pepperGrayImH')

subplot(2,2,4);
imshow(pepperGrayImF)
title('pepperGrayImF')


fprintf('-------- Finish Solving Problem 2 --------\n')
pause;

%Problem 3

%personal function
[maxValue, minValue, meanValue, medianValue] = FindInfo(pepperGrayIm);

%built in matlab functions
maxBuilt = max(pepperGrayIm, [], 'all');
minBuilt = min(pepperGrayIm, [], 'all');
meanBuilt = mean(pepperGrayIm, 'all');
medianBuilt = median(pepperGrayIm, 'all');

if maxValue == maxBuilt
    fprintf('Max values matched!\n');
else
    fprintf('Max values did not match.\n');
end

if minValue == minBuilt
    fprintf('Min values matched!\n');
else
    fprintf('Min values did not match.\n');
end

if meanValue == meanBuilt
    fprintf('Mean values matched!\n');
else
    fprintf('Mean values did not match.\n');
end

if medianValue == medianBuilt
    fprintf('Median values matched!\n');
else
    fprintf('Medain values did not match.\n');
end

fprintf('-------- Finish Solving Problem 3 --------\n')
pause;

%Problem 4

%normalizing image to values between 0 and 1
pepperGrayImN = double(pepperGrayIm)/254;

figure;
imshow(pepperGrayImN);
title('Normalized Grayscale Image');

%create an array that will raise the values of the image by specific powers
powerOf = [1.25* ones(row/4, col); ones(row/4, col); .75*ones(row/4,col); ones(row/4,col)];
pepperGrayImP = pepperGrayImN .^ powerOf;

figure;
imshow(pepperGrayImP);
title('Processed Grayscale Image');

%save image to file
imwrite(pepperGrayImP,'RileyDensley_pepperGrayImP.jpg')
    
fprintf('-------- Finish Solving Problem 4 --------\n')
pause;

%Problem 5

bw1 = pepperGrayImN;
%saves vector values of all elements that meet criteria
upper = find(pepperGrayImN > .35);
lower = find(pepperGrayImN <= .35);
%sets all the elemets that correspond to the vector values to either 1 or 0
bw1(upper) = 1;    
bw1(lower) = 0;

%use logical & to create array of 0 and 1
bw2ones = ones(row, col);
bw2 = double((pepperGrayImN > .35) & bw2ones);

%Use built in function
bw3 = double(im2bw(pepperGrayImN, 0.35));


if bw1 == bw3 & bw2 == bw3
    fprintf('Both of my methods worked\n');
elseif bw1 == bw3
    fprintf('My method 1 worked but not my method 2\n');
elseif bw2 == bw3
    fprintf('My method 2 worked but not my method 1\n');
else
    fprintf('Both of my two methods did not work\n');
end

figure;
subplot(1,3,1);
imshow(bw1)
title('My First Method')

subplot(1,3,2);
imshow(bw2)
title('My Second Method')

subplot(1,3,3);
imshow(bw3)
title('Matlab method')


fprintf('-------- Finish Solving Problem 5 --------\n')
pause;

%problem 6

%personal function
[pepperImBlur] = BlurImage(pepperIm);
[pepperGrayImBlur] = BlurImage(pepperGrayIm);

figure;
subplot(2,2,1);
imshow(pepperIm)
title('pepperIm')

subplot(2,2,2);
imshow(pepperImBlur)
title('pepperImBlur')

subplot(2,2,3);
imshow(pepperGrayIm)
title('pepperGrayIm')

subplot(2,2,4);
imshow(pepperGrayImBlur)
title('pepperGrayImBlur')


fprintf('-------- Finish Solving Problem 6 --------\n')
pause;

%problem 7

close all;
clear all;