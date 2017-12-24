% Read image
imgPath = '../res/test5.png';
rgbImg = imread(imgPath);
grayImg = rgb2gray(rgbImg);

% Produce noise image
noiseImg = noise(rgbImg);
% Produce direction image
directionImg = direction(rgbImg);
% Produce texture image
textureImg = convolution(noiseImg, directionImg);
% Produce outline image
outlineImg = outline(rgbImg);

% Combine images
resultGrayImg = uint8((double(textureImg) + double(outlineImg) + double(grayImg)) ./ 3);
textureImg = repmat(double(textureImg), 1, 1, 3);
outlineImg = repmat(double(outlineImg), 1, 1, 3);
resultImg = uint8((textureImg + outlineImg + double(rgbImg)) ./ 3);

