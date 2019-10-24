% Assignment 3
% Riley Densley
% A01227345

circuitIm = imread('Circuit.jpg');

% Problem I
% Problem I.1

mask3x3 = [1 2 1; 2 4 2; 1 2 1] /16;
mask5x5 = ones(5)/25;

% range = [0, 255];
% [scaledFoodIm, transFunc] = Scaling(circuitIm, [-60, 50]);
% [scaledFoodIm, transFunc] = Scaling(circuitIm, [60, 25]);
% [scaledFoodIm, transFunc] = Scaling(circuitIm, [0, 25.5]);
% [scaledFoodIm, transFunc] = Scaling(circuitIm, range);

circuitImWeightedAverageFilter = AverageFiltering(circuitIm, mask3x3);
circuitImNormalAverageFilter = AverageFiltering(circuitIm, mask5x5);

figure;
sgtitle("Average Filter");

subplot(1,3,1);
imshow(circuitIm);
title('Original Image');

subplot(1,3,2);
imshow(circuitImWeightedAverageFilter);
title('Weighted Filter');

subplot(1,3,3);
imshow(circuitImNormalAverageFilter);
title('Normal Filter');
truesize([270,270]);

fprintf('-------- Finish Solving Problem I.1 --------\n')
pause;

% Problem I.2

mask3x3 = [1 2 1; 2 4 2; 1 2 1];
mask5x5 = ones(5);

circuitImWeightedMedianFilter = MedianFiltering(circuitIm, mask3x3);
circuitImNormalMedianFilter = MedianFiltering(circuitIm, mask5x5);

figure;
sgtitle("Median Filter");

subplot(1,3,1);
imshow(circuitIm);
title('Original Image');

subplot(1,3,2);
imshow(circuitImWeightedMedianFilter);
title('Weighted Filter');

subplot(1,3,3);
imshow(circuitImNormalMedianFilter);
title('Normal Filter');
truesize([270,270]);

fprintf('-------- Finish Solving Problem I.2 --------\n')
pause;

% Problem I.3

lapMask = [-1, -1, -1; -1, 8, -1; -1, -1, -1];

moonIm = imread('Moon.jpg');

%moonImFiltered = filtering func
moonImFiltered = conv2(double(moonIm), lapMask, 'same');

moonImEnhanced = moonIm + uint8(moonImFiltered);

figure;
sgtitle("Median Filter");

subplot(2,2,1);
imshow(moonIm);
title('Original Image');

subplot(2,2,2);
imshow(uint8(moonImFiltered));
title('Filtered Image');

subplot(2,2,3);
imshow(uint8(255*mat2gray(moonImFiltered)));
title('Scaled Filtered Image');

subplot(2,2,4);
imshow(moonImEnhanced);
title('Enhanced Image');
truesize([220,220]);

fprintf('-------- Finish Solving Problem I.3 --------\n')
pause;

% Problem II.1

riceIm = imread('Rice.jpg');

gxMask = [-1, -2, -1; 0, 0, 0; 1, 2, 1];
gyMask = [-1, 0, 1; -2, 0, 2; -1, 0, 1];

gxTotal = conv2(riceIm, gxMask, 'same');
gyTotal = conv2(riceIm, gyMask, 'same');

riceImGradF = (gxTotal.^2 + gyTotal.^2);
tresh = 2*sqrt(mean(riceImGradF, 'all'));
% 226.6821
riceImEdge = sqrt(riceImGradF);
riceImEdgeThresh = riceImEdge > tresh;


fprintf('-------- Finish Solving Problem II.1 -------\n')
pause;

% Problem II.2
bin = 18;
riceEdgeHist = CalEdgeHist(riceIm, bin);

figure;
subplot(1,3,1);
imshow(riceIm);
title("Original Image");

subplot(1,3,2);
imshow(riceImEdgeThresh);
title("Edge Ddetection Image");

angles = 1:360/bin:360;

subplot(1,3,3);
bar(angles, riceEdgeHist);
xlabel("Angle");
ylabel("Count");
title("Edge Hist");
truesize([270,270]);


fprintf('-------- Finish Solving Problem II.2 -------\n')
pause;

% Problem III

fprintf("For the removing streaks the best option I found\n");
fprintf("was to simply set a threshold. Since the writing\n");
fprintf("was the darkest part for most of the images, setting\n");
fprintf("a threshold to 100 cleaned up most of the streaking.\n");

textIm = imread('Text.gif');

textImClean = RemoveStreaks(textIm);

text1Im = imread('Text1.gif');

text1ImClean = RemoveStreaks(text1Im);

text2Im = imread('Text2.jpg');

text2ImClean = RemoveStreaks(text2Im);


fprintf('-------- Finish Solving Problem III --------\n')
pause;

close all;
