clear all;
imtool close all;
close all;
clc;
vid = videoinput('winvideo', 1, 'YUY2_160x120');
preview(vid);
pause(3);
ip=(ycbcr2rgb(getsnapshot(vid)));
input('press enter')
number=0;
subplot(2,2,1)
imshow(ip);
title('input image');
[x y z]=size(ip);
for(j=1:y)
    for(i=1:x)
        if(ip(i,j,3)>(0.836*ip(i,j,2))-14)
            if(ip(i,j,3)<(0.836*ip(i,j,2))+44)
            else
                ip(i,j,1)=0;
                ip(i,j,2)=0;
                ip(i,j,3)=0;
            end
        else
            ip(i,j,1)=0;
            ip(i,j,2)=0;
            ip(i,j,3)=0;
        end
    end
end
subplot(2,2,2)
imshow(ip);
title('Image after color filtering part 1');
for(j=1:y)
    for(i=1:x)
        if(ip(i,j,3)>(0.79*ip(i,j,2))-67)
            if(ip(i,j,3)<(0.78*ip(i,j,2))+42)
            else
                ip(i,j,1)=0;
                ip(i,j,2)=0;
                ip(i,j,3)=0;
            end
        else
            ip(i,j,1)=0;
            ip(i,j,2)=0;
            ip(i,j,3)=0;
        end
    end
end
subplot(2,2,3)
imshow(ip)
title('Image after color filtering part 2');
%% %%%%%%%%%%%%%%%%%%%%%%%%% HSV FILTER %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

[H S V]=rgb2hsv(ip);
[x y]=size(H);
% imtool(H);
for(j=1:y)
    for(i=1:x)
        if(H(i,j)<0.15)
            if(H(i,j)>0)
                H(i,j)=1;
            else
                H(i,j)=0;
            end
        else
            H(i,j)=0;
        end
    end
end
subplot(2,2,4)
imshow(H);
title('Image after HSV filtering -1');



