function [ output_img ] = outline( input_img )
%OUTLINE produces an outline image based on 霓虹变换

[height, width, channel] = size(input_img);
output_img = zeros(height, width, channel);
input_img = padarray(input_img, [1, 1], 'post');
input_img = double(input_img);
for row = 1:height
    for col = 1:width
        row_1 = row + 1;
        col_1 = col + 1;
        t1 = input_img(row, col, :) - input_img(row_1, col, :);
        t2 = input_img(row, col, :) - input_img(row, col_1, :);
        output_img(row, col, :) = 2 * sqrt((t1) .^ 2 + (t2) .^ 2);
    end
end

output_img = uint8(output_img);
output_img = rgb2gray(output_img);
output_img = 255 - output_img;
output_img(output_img < 75) = 0;

end

