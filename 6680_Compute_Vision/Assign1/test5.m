%disp(pepperGrayImN)

bw1 = pepperGrayImN;
upper = find(pepperGrayImN > .35);
lower = find(pepperGrayImN <= .35);

bw1(upper) = 1;    
bw1(lower) = 0;
imshow(bw1);

bw2 = ones(row, col);
bw2 = (pepperGrayImN > .35) && bw2;
imshow(bw2);