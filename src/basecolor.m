function [ bc, sbc ] = basecolor( C, K )
%BASECOLOR chooses main and sub colors for clusters
% of kmeans result
% C - Cluster centroid locations
% K - The number of clusters

rw = 0.3; gw = 0.59; bw = 0.11;
a1 = 0.5; a2 = 0.5;
bclib = [
    154, 35, 27;
    242, 74, 27;
    255, 255, 0;
    161, 209, 147;
    1, 164, 59;
    1, 81, 152;
    20, 25, 44;
    51, 186, 205;
    153, 88, 178;
    255, 76, 186;
    107, 17, 107;
    72, 74, 37
];
bc = zeros(K, 3);
sbc = zeros(K, 3);
for i = 1:K
    min = inf;
    mincolor = zeros(1, 3);
    for j = 1:12
        d = rw * sqrt((C(i, 1) - bclib(j, 1))^2) + ...
            gw * sqrt((C(i, 2) - bclib(j, 2))^2) + ...
            bw * sqrt((C(i, 3) - bclib(j, 3))^2);
        if (d < min)
            min = d;
            mincolor = bclib(j,:);
        end
    end
    bc(i,1:3) = mincolor;
end

for i = 1:K
    mindistance = inf;
    mincolor = inf;
    for j = 1:12
        if (bc(i) == bclib(j))
            continue;
        end
        color = [C(i,:); bc(i,:); bclib(j,:); (bc(i,:) + bclib(j,:)) ./ 2];
        color = transpose(color);
        weight = [(1-a1)*(1-a2); a1*(1-a2); (1-a1)*a2; a1*a2];
        mapcolor = color * weight;
        d = rw * sqrt((C(i, 1) - mapcolor(1))^2) + ...
            gw * sqrt((C(i, 2) - mapcolor(2))^2) + ...
            bw * sqrt((C(i, 3) - mapcolor(3))^2);
        if (d < mindistance)
            mindistance = d;
            mincolor = j;
        end
    end
    sbc(i, 1:3) = bclib(mincolor,:);
end

end

