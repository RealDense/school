% Assignment 4
% Riley Densley
% A01227345

close all

sampleIm= imread('Sample.jpg');

% Problem I
% Problem I.1

% make filter
[M,N] = size(sampleIm);
sigx = 25;
sigy = 75;
gaus = zeros(M,N);
for u = 1:M
    for v = 1:N
        x = sqrt((u - M/2 + 1)^2);
        y = sqrt((v - N/2 + 1)^2);
        gaus(u,v) = exp(-((x)^2/(2*sigx*sigx) + (y)^2/(2*sigy*sigy)));
    end
end


figure;
sgtitle("Gaussian Low-pass Filter");

subplot(1,3,1);
imshow(uint8(sampleIm));
title('Original Image');

subplot(1,3,2);
imshow((gaus));
title('Gaussian Low-pass Filter');

% gaus = gaus ./ (sum(gaus, 'all'));

imft = fft2(sampleIm);
imftsh = fftshift(imft);
% gausft = fft2(gaus);
imBlur = imftsh .* gaus;
imBlursh = ifftshift(imBlur);
sampleImBlur = ifft2(imBlursh);
% imftsh = fftshift(imft);

subplot(1,3,3);
% imshow(conv2(sampleIm, gaus, 'same'));
imshow(uint8(real(sampleImBlur)));
% imshow(abs(fftshift(imft)));
title('Filtered Image');
truesize([270,270]);

fprintf('-------- Finish Solving Problem I.1 --------\n')
pause;

% Problem I.2

[M,N] = size(sampleIm);
butter = zeros(M,N);
for u = 1:M
    for v = 1:N
        x = u - M/2 + 1;
        y = v - N/2 + 1;
        butter(u,v) =  1/(1+((40 / sqrt(x^2 + y^2))^(2*2))); %exp(-((x)^2/(2*sigx*sigx) + (y)^2/(2*sigy*sigy)));
    end
end


figure;
sgtitle("Butterworth High-pass Filter");

subplot(1,3,1);
imshow(sampleIm);
title('Original Image');

subplot(1,3,2);
imshow(butter);
title('Butterworth High-pass Filter');

samplefft = fftshift(fft2(sampleIm));
sampleButter = samplefft .* butter;
sampleButter = ifft2(ifftshift(sampleButter));

subplot(1,3,3);
% imshow(imfilter(sampleIm, butter));
imshow(uint8(real(sampleButter)));
title('Filtered Image');
truesize([270,270]);

fprintf('-------- Finish Solving Problem I.2 --------\n')
pause;

% Problem II.1

cityIm = imread('City.jpg');

[M,N] = size(cityIm);
H = zeros(M,N);
k = 0.0025;
for u = 1:M
    for v = 1:N
        x = u - M/2 + 1;
        y = v - N/2 + 1;
        H(u,v) =  exp(-k * (sqrt(x^2 + y^2)^(5/3)));
    end
end

%%%%% Blur IMAGE
cityImBlur = ifft2(ifftshift(fftshift(fft2(cityIm)).*H));

figure;
sgtitle("Noisy Filter");

subplot(1,3,1);
imshow(cityIm);
title('Original Image');

subplot(1,3,2);
imshow(H);
title('Noise Filter');

subplot(1,3,3);
imshow(uint8(real(cityImBlur)));
title('Noisy Image');
truesize([270,270]);


imwrite(uint8(real(cityImBlur)), 'BlurCity.bmp');


fprintf('-------- Finish Solving Problem II.1 --------\n')
pause;

% Problem II.2

blurCityIm = imread('BlurCity.bmp');

[M,N] = size(blurCityIm);
F = zeros(M,N);
k = 0.0025;
for u = 1:M
    for v = 1:N
        x = abs(u - M/2 + 1);
        y = abs(v - N/2 + 1);
        H =  exp(-k*(sqrt(x^2 + y^2)^(5/3)));
        F(u,v) = ((abs(H)^2)/(H*(abs(H)^2 + 0.0025)));
    end
end

cityImUnBlur = ifft2(ifftshift(fftshift(fft2(blurCityIm)).*F));

figure;
sgtitle("Unnoisy Filter");

subplot(1,3,1);
imshow(blurCityIm);
title('Original Image');

subplot(1,3,2);
imshow(F);
title('Unoise Filter');

subplot(1,3,3);
imshow(uint8(real(cityImUnBlur)));
title('Noisy Image');
truesize([270,270]);


fprintf('-------- Finish Solving Problem II.2 --------\n')
pause;

% Problem III.1

capitalIm = fftshift(fft2(imread('Capital.jpg')));
capitalMag = sqrt(real(capitalIm).^2 + imag(capitalIm).^2);
capitalPhase = atan2(imag(capitalIm), real(capitalIm));

sampleIm = fftshift(fft2(imread('Sample.jpg')));
sampleMag = sqrt(real(sampleIm).^2 + imag(sampleIm).^2);
samplePhase = atan2(imag(sampleIm), real(sampleIm));

showCapitalMag = scaler(capitalMag, true);
showCapitalPhase = scaler(capitalPhase, false);
showSampleMag = scaler(sampleMag, true);
showSamplePhase = scaler(samplePhase, false);

figure
sgtitle('Magnitude and Phase');

subplot(2,2,1);
imshow(showCapitalMag);
title("City Magnitude");

subplot(2,2,2);
imshow(showCapitalPhase);
title("City Phase");

subplot(2,2,3);
imshow(showSampleMag);
title("Sample Magnitude");

subplot(2,2,4);
imshow(showSamplePhase);
title("Sample Phase");
truesize([200,200]);


fprintf('-------- Finish Solving Problem III.1 --------\n')
pause;

% Problem III.2

CPSM = sampleMag .* exp(1i * capitalPhase);
SPCM = capitalMag .* exp(1i * samplePhase);

CPSM = ifft2(ifftshift(CPSM));
SPCM = ifft2(ifftshift(SPCM));

figure
sgtitle('Mixing Magitude and Phase');

subplot(1,2,1);
imshow(uint8(CPSM));
title("Capital phase on Sample Magnitude");

subplot(1,2,2);
imshow(uint8(SPCM));
title("Sample Phase on Capital Magnitude");
truesize([270,270]);

fprintf('-------- Finish Solving Problem III.2 --------\n')
pause;

% Problem IV.1

boyNoisyIm = imread('boy_noisy.gif');

bniFFT = fftshift(fft2(boyNoisyIm));

fprintf('-------- Finish Solving Problem IV.1 --------\n')
pause;

% Problem IV.2

highFreq = chooseMag(bniFFT);

fprintf('-------- Finish Solving Problem IV.2 --------\n')
pause;

% Problem IV.3

newFreq = replaceFrequency(bniFFT, highFreq);

fprintf('-------- Finish Solving Problem IV.3 --------\n')
pause;

% Problem IV.4

bni = ifft2(ifftshift(newFreq));

figure
sgtitle('Noisy Boy');

subplot(1,2,1);
imshow(boyNoisyIm);
title("Original Image");

subplot(1,2,2);
imshow(uint8(real(bni)));
title("Filtered Image");
truesize([270,270]);

fprintf('-------- Finish Solving Problem IV.4 --------\n')
pause;

% Problem V.1

lenaIm = imread('Lena.jpg');
[row,col] = size(lenaIm);

maxLevel = log2(min(row,col));
[C, S] = wavedec2(lenaIm, maxLevel, 'haar');
lenaRestore = uint8(waverec2(C,S,'haar'));


if lenaIm == lenaRestore
    fprintf('Lena and Lena are the same\n');
else
    fprintf('Lena is not Lena..... That is bad\n');
end

fprintf('-------- Finish Solving Problem V.1 --------\n')
pause;

% Problem V.2
dwtmode('per');

[cA1,cH1,cV1,cD1] = dwt2(lenaIm,'db2');
[cA2,cH2,cV2,cD2] = dwt2(cA1,'db2');
[cA3,cH3,cV3,cD3] = dwt2(cA2,'db2');

cA3mod = cA3; 

[row, col] = size(cA3mod);
for x = 1:row:2
    for y = 1:col:2
        cA3mod(x:x+1, y:y+1) = ones(2) * sum(cA3mod(x:x+1, y:y+1), 'all');
    end
end

cH3mod = zeros(size(cH3));
cV1mod = zeros(size(cV1));

lenaImAve = idwt2(cA3mod, cH3, cV3, cD3, 'db2');
lenaImAve = idwt2(lenaImAve, cH2, cV2, cD2, 'db2');
lenaImAve = idwt2(lenaImAve, cH1, cV1, cD1, 'db2');

lenaImV = idwt2(cA3, cH3, cV3, cD3, 'db2');
lenaImV = idwt2(lenaImV, cH2, cV2, cD2, 'db2');
lenaImV = idwt2(lenaImV, cH1, cV1mod, cD1, 'db2');

lenaImClean = idwt2(cA3mod, cH3mod, cV3, cD3, 'db2');
lenaImClean = idwt2(lenaImClean, cH2, cV2, cD2, 'db2');
lenaImClean = idwt2(lenaImClean, cH1, cV1, cD1, 'db2');

figure
% subplot(1,3,1);
imshow(uint8(lenaImAve));
title("Averaging Image");
% truesize([270,270]);

figure
% subplot(1,3,2);
imshow(uint8(lenaImV));
title("Vertical Zeros");
% truesize([270,270]);

figure
% subplot(1,3,3);
imshow(uint8(lenaImClean));
title("Horizontal Zeros");
% truesize([270,270]);

fprintf('-------- Finish Solving Problem V.2 --------\n')
pause;

% Problem VI.1

lenaImNoisy = imnoise(lenaIm, 'gaussian', 0, 0.01);

dwtmode('per');

[cA1,cH1,cV1,cD1] = dwt2(lenaImNoisy,'db2');
[cA2,cH2,cV2,cD2] = dwt2(cA1,'db2');
[cA3,cH3,cV3,cD3] = dwt2(cA2,'db2');

var1 = noiseV(cH1, cV1, cD1);
thres1 = threshold(var1);
[cH1m, cV1m, cD1m] = modifyW(cH1, cV1, cD1, thres1);

var2 = noiseV(cH2, cV2, cD2);
thres2 = threshold(var2);
[cH2m, cV2m, cD2m] = modifyW(cH2, cV2, cD2, thres2);

var3 = noiseV(cH3, cV3, cD3);
thres3 = threshold(var3);
[cH3m, cV3m, cD3m] = modifyW(cH3, cV3, cD3, thres3);

% size(cA3)
% size(cH3m)
% size(cV3m)
% size(cD3m)

lenaImClean = idwt2(cA3, cH3m, cV3m, cD3m, 'db2');
lenaImClean = idwt2(lenaImClean, cH2m, cV2m, cD2m, 'db2');
lenaImClean = idwt2(lenaImClean, cH1m, cV1m, cD1m, 'db2');

figure
sgtitle('Noisy Lena');

subplot(1,2,1);
imshow(lenaImNoisy);
title("Noisy Image");

subplot(1,2,2);
imshow(uint8(real(lenaImClean)));
title("Cleaned Image");
truesize([270,270]);

fprintf('-------- Finish Solving Problem VI.All --------\n')
pause;

close all;

