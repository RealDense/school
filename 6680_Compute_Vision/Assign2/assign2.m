% Assignment 2
% Riley Densley
% A01227345

foodIm = imread('Food.jpg');

%Problem 1
range = [0, 255];
[scaledFoodIm, transFunc] = Scaling(foodIm, [-60, 50]);
[scaledFoodIm, transFunc] = Scaling(foodIm, [60, 25]);
[scaledFoodIm, transFunc] = Scaling(foodIm, [0, 25.5]);
[scaledFoodIm, transFunc] = Scaling(foodIm, range);

%FIX TRANS FUNCTION
figure;
plot(transFunc);
xlabel('Original Intensity');
ylabel('New Intensity');


fprintf('-------- Finish Solving Problem 1 --------\n')
pause;

%Problem 2

minOriIntensity = min(foodIm, [], "all");
maxOriIntensity = max(foodIm, [], "all");

matScaledFoodIm = imadjust(foodIm, double([minOriIntensity, maxOriIntensity])/255, range/255);
imwrite(matScaledFoodIm, "matScaledFoodIm.jpg");

figure;
subplot(1,2,1);
imshow(scaledFoodIm);
title("My Scaled Image");

subplot(1,2,2);
imshow(matScaledFoodIm);
title("Matlab Scaled Image");


%change image to gray scale

%pepperGrayIm = rgb2gray(pepperIm);

%get the size of the image
%[row, col, channel] = size(pepperIm);

fprintf('-------- Finish Solving Problem 2 --------\n')
pause;

% Problem 3

histScaledFoodIm = CalHist(scaledFoodIm, false, false);
normHistScaledFoodIm = CalHist(scaledFoodIm, true, false);
histMatScaledFoodIm = CalHist( matScaledFoodIm, false, true);

figure;
subplot(2,2,3);
plot(histMatScaledFoodIm(1, 1:256));
title("matScaledFoodIm");
xlabel("Intensity");
ylabel("Count");

subplot(2,2,1);
plot(histMatScaledFoodIm(2, 1:256));
title("normMatScaledFoodIm");
xlabel("Intensity");
ylabel("Frequency");

subplot(2,2,2);
plot(normHistScaledFoodIm);
title("normHistScaledFoodIm");
xlabel("Intensity");
ylabel("Frequency");

subplot(2,2,4);
plot(histScaledFoodIm);
title("histScaledFoodIm");
xlabel("Intensity");
ylabel("Count");


fprintf('-------- Finish Solving Problem 3 --------\n')
pause;

% Problem 4

tic;
[equalizedFoodIm, equalizedTransFunc] = HistEqualization(foodIm);
myTime = toc;
fprintf('My eqaulization running time is %f\n', myTime);
%myTime

fprintf('-------- Finish Solving Problem 4 --------\n')
pause;

% Problem 5

tic;
[matEqualizedFoodIm, matEqualizedTransFunc] = histeq(foodIm);
matTime = toc;
fprintf('Matlab eqaulization running time is %f\n', matTime);
fprintf('\nThe difference in time was %f seconds\n', matTime - myTime);
if(myTime < matTime)
    fprintf('My function was faster!\n\n');
else
    fprintf('MatLABs funciton was faster.\n\n');
end
%matTime

figure;
subplot(1,2,1);
imshow(matEqualizedFoodIm);
title("matEqualizedFoodIm");

subplot(1,2,2);
imshow(equalizedFoodIm);
title("equalizedFoodIm");

figure;
subplot(1,2,1);
plot(matEqualizedTransFunc*255);
title("matEqualizedTransFunc");
xlabel("Intensity");
ylabel("Frequency");

subplot(1,2,2);
plot(equalizedTransFunc);
title("equalizedTransFunc");
xlabel("Intensity");
ylabel("Frequency");

fprintf("\nThe two images from my equalization function and matLabs look the same.\n");
fprintf("Since they look the exact same their histograms must be very similar.\n\n");

fprintf("I didn't have any findings after reading and using the matLab equalization.\n");
fprintf("I kept my function the same.\n\n");

fprintf('-------- Finish Solving Problem 5 --------\n')
pause;

close all;