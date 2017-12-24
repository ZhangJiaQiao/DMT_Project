function output_img=texture(input_img)
    texture_input=imread('texture.jpg');
    texture_input=rgb2gray(texture_input);
    [m,n]=size(input_img);
    texture_input=imresize(texture_input,[m,n]);
    mean_texture=mean(mean(texture_input));
    k=1;
    output_img=input_img-k*(texture_input-mean_texture);
end