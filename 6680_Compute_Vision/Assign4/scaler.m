% Assignment 4
% Riley Densley
% A01227345

function [scaledIm] = scaler(im, mag)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here


scaledIm = im;
if mag
    scaledIm = log(im);
end
scaledIm = scaledIm - min(scaledIm, [], 'all');
scaledIm = scaledIm ./ max(scaledIm, [], 'all');
end

