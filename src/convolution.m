function output_img = convolution(input_img,direction_img)
    length = 5;
    [row,col] = size(input_img);
    padRow = row+2*length;
    padCol = col+2*length;
    inputPadding = zeros(padRow, padCol);
    inputPadding(length+1:row+length, length+1:col+length) = double(input_img);

    deltaS = linspace(0, length, length+1);
    S = linspace(0, 0, length+1);
    for i = 2 : length + 1
        S(i) = S(i-1) + deltaS(i-1);
    end
    kw = hanning(S(length+1) + deltaS(length+1) + 1, 'periodic');
    h = linspace(0,0,length+1);
    for i = 1 : length + 1
        h(i) = sum(kw(S(i)+1:S(i)+deltaS(i)+1));
    end
    h45 = zeros(length+1, length+1);
    h135 = zeros(length+1, length+1);
    count45 = 1;
    count135 = 1;
    for i = 1 : length + 1
        for j = 1 : length + 1
            if i == j
                h135(i,j) = h(count45);
                count45 = count45 + 1;
            end
            if i == length + 2 - j
                h45(i,j) = h(count135);
                count135 = count135 + 1;
            end
        end
    end

    inputPadding = inputPadding / (sum(h)*2);
    g = zeros(row,col);
    for x = length+1 : row+length
        for y = length+1: col+length
            if direction_img(x-length,y-length) == 0
                g(x-length,y-length) = sum((inputPadding(x,y:y+length) + inputPadding(x,y-length:y)) .* h);
            elseif direction_img(x-length,y-length) == 90
                g(x-length,y-length) = sum((inputPadding(x:x+length,y) + inputPadding(x-length:x,y)) .* h');
            elseif direction_img(x-length,y-length) == 45
                g(x-length,y-length) = sum(sum((inputPadding(x:x+length,y:y+length) + inputPadding(x-length:x,y-length:y)) .* h45));
            else
                g(x-length,y-length) = sum(sum((inputPadding(x:x+length,y:y+length) + inputPadding(x-length:x,y-length:y)) .* h135));
            end
        end
    end

    output_img = uint8(g);
end

