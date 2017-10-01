clc;
clear;

origin=imread('C:\Users\alienware\Desktop\DMT\DMT_Project-master\resources\samplePicture.bmp');
hsv=rgb2hsv(origin);
figure ,imshow(hsv);
figure ,imshow(origin);
h=hsv(:,:,1);
s=hsv(:,:,2);
v=hsv(:,:,3);

k=0;

[m,n]=size(h);
[count,xl]=imhist(h);
[x,y]=size(count);

for i=1:x
    if(count(i,1)>=500)
        k=k+1;
    end
end

trans_h=reshape(h,m*n,1);
trans_s=reshape(s,m*n,1);
trans_v=reshape(v,m*n,1);
trans_hsv=[trans_h,trans_s,trans_v];
[idx,centroid]=kmeans(trans_hsv,k);

trans_hsv(:,:)=centroid(idx,:);

new_h=reshape(trans_hsv(:,1),m,n);
new_s=reshape(trans_hsv(:,2),m,n);
new_v=reshape(trans_hsv(:,3),m,n);



hsv(:,:,1)=new_h;
hsv(:,:,2)=new_s;
hsv(:,:,3)=new_v;

figure ,imshow(hsv2rgb(hsv));