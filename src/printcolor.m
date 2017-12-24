function [ retImg ] = printcolor( img, labels, C, bc )
%PRINTCOLOR prints a image based on base colors and sub base colors
    
[height, width, channel] = size(img);
retImg = zeros(size(img));
idx = reshape(labels, [height, width]);
for row = 1:height
    for col = 1:width
        i = idx(row, col);
        retImg(row, col, :) = C(i, :);
    end
end
retImg = uint8(retImg);

end
