% Read image
imgpath = '../res/lenna.png';
rgbimg = imread(imgpath);
grayimg = rgb2gray(rgbimg);

% Determine the value of k
% hsvimg = rgb2hsv(rgbimg);
% [freq, val] = imhist(hsvimg(:,:,1));
% k = 0;
% thres = 1000;
% for i = 1:256
%     if (freq(i) > thres)
%         k = k + 1;
%     end
% end

k = 4;

% Compute kmeans
[idx, C]= kmeansby(rgbimg, k);

% Choose base colors
[bc, sbc] = basecolor(C, k);

% Print image with base colors
colorImg = printcolor(rgbimg, idx, C, bc);

% Produce noise image
noiseImg = noise(rgbimg);
% Produce direction image
directionImg = direction(rgbimg);
% Produce texture image
textureImg = convolution(noiseImg, directionImg);

% Produce outline image
outlineImg = outline(rgbimg);

% Combine images
textureImg = repmat(double(textureImg), 1, 1, 3);
outlineImg = repmat(double(outlineImg), 1, 1, 3);
colorImg = double(colorImg);
resultImg = uint8((textureImg + outlineImg + colorImg) ./ 3);

