% Assingment 2
% Riley Densley
% A01227345

function [scaledIm, transFunc] = Scaling(inputIm,range)
%Scaling Summary of this function goes here
%   Detailed explanation goes here

% Check for valid range
oriMinIntensity = min(inputIm,[],"all");
oriMaxIntensity = max(inputIm, [], "all");

scaledIm = inputIm;

transFunc = 0;

minIntensity = range(1);
maxIntensity = range(2);
if(minIntensity < 0 || maxIntensity < 0)
    fprintf("Error: negative number not allowed\n");
elseif minIntensity > maxIntensity
    fprintf("Error: min value must be smaller than max value\n");
elseif ~(minIntensity == round(minIntensity) && maxIntensity == round(maxIntensity))
    fprintf("Error: range must be integers\n");
else

    c = double(maxIntensity - minIntensity) / double(oriMaxIntensity - oriMinIntensity);

    b = double(minIntensity) - c * double(oriMinIntensity);

    scaledIm = uint8(c * double(inputIm) + b);
    %intensity = linspace(oriMinIntensity, oriMaxIntensity, oriMaxIntensity-oriMinIntensity);
    %transFunc = oriMinIntensity:oriMaxIntensity;
    transFunc = uint8(c * double(oriMinIntensity:oriMaxIntensity) + b);
    
    min(scaledIm,[],"all");
    max(scaledIm,[],"all");

end

