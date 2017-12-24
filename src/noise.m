function output_img=noise(input_img)
    input_img=rgb2gray(input_img);
    k=[0.9 0.7 0.7];
    noise_min=[5 25 80];
    noise_max=255;
    %p=double(p); %û����ɫ����ǰ��ͼ��
    input_img=double(input_img)*1.5;
    l=[24 79];
    [m,n]=size(input_img);
    r=rand(m,n);
    noise_img=zeros(m,n);
    for i=1:m
        for j=1:n
            t=(1-input_img(i,j)/255)*k;
            if (input_img(i,j)<=l(1))
                if (r(i,j)>=t(1))
                    noise_img(i,j)=noise_max;
                else
                    noise_img(i,j)=noise_min(1);
                end 
            elseif l(1)<input_img(i,j)<=l(2) 
                if (r(i,j)>=t(2))
                    noise_img(i,j)=noise_max;
                else
                    noise_img(i,j)=noise_min(2);
                end
            elseif l(2)<input_img(i,j)
                if (r(i,j)>=t(3))
                    noise_img(i,j)=noise_max;
                else
                    noise_img(i,j)=noise_min(3);
                end
            end
        end
    end
    output_img=uint8(noise_img);
end