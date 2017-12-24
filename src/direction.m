function directionp = direction(input_img)
    input_img=double(rgb2gray(input_img));
    m = 7;
    theshold = 2;
    
    [row, col] = size(input_img);
    maxNumber = ceil(max(row / m, col / m)); %15*15�Ĵ���ĳ������������
    inputPadding = zeros(maxNumber * m, maxNumber * m);
    inputPadding(1:row, 1:col) = input_img;
    centerx = ceil(m / 2);
    centery = ceil(m / 2);
    r = unidrnd(4,maxNumber,maxNumber);

    count = 0; %��¼û���жϵ�����ĵ�ĸ���
    for a = 1 : maxNumber
        for b = 1 : maxNumber
            f = fft2(inputPadding((a-1)*m+1:a*m, (b-1)*m+1:b*m));
            f = fftshift(f);
            f = abs(f);
            f(centerx,centery) = 0;
            average = mean(mean(f));
            maxPoint = max(max(f));
            [maxRow, maxCol] = find(f == maxPoint, 1);
            if(maxPoint / average > theshold)
                if(maxRow - centerx == maxCol - centery)
                    temp = 45 * ones(m,m);
                elseif(maxRow - centerx == centery - maxCol)
                    temp = -45 * ones(m,m);
                elseif(maxRow-centerx == 0)
                    temp = 90 * ones(m,m);
                else
                    temp = 0 * ones(m,m);
                end
            else
                count = count + 1;
                temp = (r(a,b) - 2) * 45 * ones(m,m);
            end
            inputPadding((a-1)*m+1:a*m, (b-1)*m+1:b*m) = temp;
        end
    end
    directionp = uint8(inputPadding(1:row,1:col));

    a0 = zeros(m,m); %0
    a1 = zeros(m,m); %-45
    a2 = zeros(m,m); %45
    a3 = zeros(m,m); %90

    for a = 1 : m
        for b = 1 : m
            if a == centerx || a == centerx-1 || a == centerx+1 || a == centerx-2 || a == centerx+2
                a0(a,b) = 255;
            end
            if a == b || a == b+1 || a == b-1 || a == b+2 || a == b-2
                a1(a,b) = 255;
            end
            if a == m-b+1 || a == m-b || a == m-b+2 || a == m-b-1 || a == m-b+3
                a2(a,b) = 255;
            end
            if b == centery || b == centery-1 || b == centery+1 || b == centery-2 || b == centery+2
                a3(a,b) = 255;
            end
        end
    end

    for a = 1 : maxNumber
        for b = 1 : maxNumber
            temp = inputPadding((a-1)*m+1, (b-1)*m+1);
            if temp == 0
                inputPadding((a-1)*m+1:a*m, (b-1)*m+1:b*m) = a0;
            elseif temp == -45
                inputPadding((a-1)*m+1:a*m, (b-1)*m+1:b*m) = a1;
            elseif temp == 45
                inputPadding((a-1)*m+1:a*m, (b-1)*m+1:b*m) = a2;
            else
                inputPadding((a-1)*m+1:a*m, (b-1)*m+1:b*m) = a3;
            end
        end
    end
          
    output_img = uint8(inputPadding(1:row, 1:col));
end