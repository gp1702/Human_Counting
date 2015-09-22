clear all
close all
clc

vid = videoinput('winvideo', 1, 'YUY2_160x120');

src = getselectedsource(vid);

vid.FramesPerTrigger = 1;

vid.ReturnedColorspace = 'rgb';

preview(vid);

start(vid)
pause(3);
total=0;
input('press enter')
foregroundDetector = vision.ForegroundDetector('NumGaussians', 15, ...
    'NumTrainingFrames', 10,'LearningRate',0.02,'MinimumBackgroundRatio',0.9);
for i=1:30
    start(vid);
    frame1=rgb2gray(getdata(vid));
    subplot(2,2,1),imshow(frame1)
    title({'Input Video Sequence';[num2str(i) '-th frames']})
    frame=rgb2gray(getsnapshot(vid));
    fr_bw = step(foregroundDetector,frame);
    subplot(2,2,2),imshow(fr_bw);
    img1=rgb2gray(ycbcr2rgb(getsnapshot(vid)));
    pause(0.01);
    img2=(ycbcr2rgb(getsnapshot(vid)));
    img3=rgb2gray(img2);
    img4=rgb2hsv(img2);
    bw=bwareaopen(bwmorph(fr_bw,'open'),11);
                      %applying skin filters
    skin1=bitand((img2(:,:,3)>(0.836*img2(:,:,2)-14)) , ((img2(:,:,3)<(0.836*img2(:,:,2))+44)));
    skin2=bitand((img2(:,:,3)>(0.79*img2(:,:,2)-67)) , ((img2(:,:,3)<(0.78*img2(:,:,2))+42)));    
    skin3=~bitand(img4(:,:,1)>0,img4(:,:,1)<0.15);
    fg_and=(bitand((bitand(bw,(bitand(skin1,skin2)))),skin3));
    im_dil=imdilate(fg_and,strel('disk',10));
    im_er=imerode(im_dil,strel('disk',17));
    fg_cleaned=imfill(im_er,'holes');
    se = strel('square',15);
    Hpsf = fspecial('average', 15);
    fg_cleaned = imfilter(fg_cleaned,Hpsf,'symmetric');
    closeBW = imclose(fg_cleaned,se);
    subplot(2,2,3),imshow(closeBW);
    title('Image after filtering');
    pause(0.01);
    closeBW2=uint8(closeBW).*uint8(fr_bw);
    subplot(2,2,4),imshow(closeBW2)
    L = bwlabel(closeBW);
     if i==1
        temp=max(max(L));
        total=temp;
    end
   
    if max(max(L)) > temp
        total=total+max(max(L))-temp;
        temp=max(max(L));
    end
    if max(max(L)) < temp
        temp=max(max(L));
    end
    title({'Final Detected Object';['Total number of human counted:' num2str(total)]});
      pause(0.1);   
end

