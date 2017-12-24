function [idx, C] = kmeansby(p_rgb, k)
% kmeansby ��ͼ�����k���������ĵ�kmeans�ָ�
% p_rgb - ԭʼRGBͼ��
% k - �������ĸ���

% k��ʾ�������ĵĸ���
p_gray = rgb2gray(p_rgb); % �Ҷ�ͼ

% ��ȡͼ��ĳ���
[m, n] = size(p_gray);

p_hsv = rgb2hsv(p_rgb);

% ��ͼ�����RGB-3ͨ���ֽ�
H = reshape(p_hsv(:,:,1), m*n, 1); % �õ�һ��m*n��1�еľ��󣬴洢redֵ
S = reshape(p_hsv(:,:,2), m*n, 1); % �õ�һ��m*n��1�еľ��󣬴洢greenֵ
V = reshape(p_hsv(:,:,3), m*n, 1); % �õ�һ��m*n��1�еľ��󣬴洢blueֵ
dat = [H S V];
% �ظ�����4��

[idx, C] = kmeans(double(dat), k, 'Start','sample', 'Replicates', 4);
C = reshape(C, [1, k, 3]);
C = hsv2rgb(C);
C = reshape(C, [k, 3]);
C = C .* 255;

end