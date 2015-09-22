clear all;
close all;
clc;



%GET THE VIDEO FROM CAMERA


vid = videoinput('winvideo', 1, 'YUY2_640x480');
src = getselectedsource(vid);

vid.FramesPerTrigger = 1;

vid.ReturnedColorspace = 'rgb';

preview(vid);

start(vid);
bg=getdata(vid);
figure; 
imshow(bg);
stoppreview(vid);
bg_bw = double(rgb2gray(bg)); % convert background to greyscale
thresh=30;
% ------------------ set frame size variables -----------------------
fr_size = size(bg);
width = fr_size(2);
height = fr_size(1);
fg = zeros(height, width);
%-----compute the average of the 1st 10 frames as background--------
avebg=zeros(height, width);

for m = 1:10
    start(vid);
    fixbg=getdata(vid);
    fix_bw = rgb2gray(fixbg);
    avebg=avebg+double(fix_bw);
end
avebg=avebg/10;
% ---------------- process frames with average 10-----------------------------------
total = 0; % to initalise the total count display as 0
fullscreen = get(0,'ScreenSize');
figure('Position',[0 0 fullscreen(3) fullscreen(4)]);
for i = 11:20 % length(source)
    start(vid);
    fr=getdata(vid);
    fr_bw = rgb2gray(fr); % convert frame to grayscale
    fr_diff = abs(double(fr_bw) - double(avebg));
    fr_diff=fr_diff/(max(max(fr_diff)));   % converted to single
    % cast operands as double to avoid negative overflow
    for j=1:width
        % if fr_diff > thresh pixel in foreground
        for k=1:height
            if ((fr_diff(k,j) > thresh))
                fg(k,j) = fr_bw(k,j);
            else
                fg(k,j) = 0;
            end
        end
    end
    fg=bwareaopen(bwmorph(fg,'open'),70);
    bg_bw = fr_bw;
    subplot(2,2,1),imshow(fr_bw)
    title({'Input Video Sequence';[num2str(i) '-th frames']})
    subplot(2,2,2),imshow(uint8((fg>0).*255))
    title(['Detecting Human Object Using Thresholding'])
    fg_cleaned = bwareaopen(fg,5000);
    se = strel('square',50);
    Hpsf = fspecial('average', 15);
    fg_cleaned = imfilter(fg_cleaned,Hpsf,'symmetric');
    closeBW = imclose(fg_cleaned,se);
    subplot(2,2,3),imshow(closeBW)
    title(['Detecting Human Object Using Thresholding and Filtering'])
    closeBW2=uint8(closeBW).*fr_bw;
    subplot(2,2,4),imshow(closeBW2)
    M(i-1) = im2frame(uint8(fg_cleaned),gray);
    % put frames into movie
    L = bwlabel(closeBW);
    if i==11
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
    %% Boxing closeBW
    L = bwlabel(closeBW);
    [r, c] = find(L==1);
    top1=max(r);
    bottom1=min(r);
    right1=max(c);
    left1=min(c);
    width1=right1-left1;
    height1=top1-bottom1;
    Box1=[left1 bottom1 width1 height1];
    [r, c] = find(L==2);
    top2=max(r);
    bottom2=min(r);
    right2=max(c);
    left2=min(c);
    width2=right2-left2;
    height2=top2-bottom2;
    Box2=[left2 bottom2 width2 height2];
    %% Creating a rectangle
    if ~isempty(Box1)
        subplot(2,2,1)
        rectangle('Position',Box1,'EdgeColor','r');
    end
    if ~isempty(Box2)
        subplot(2,2,1)
        rectangle('Position',Box2,'EdgeColor','r');
    end
    pause(0.1);
end
avebg=avebg/100;
% ---------------- process frames with average 100-----------------------------------
total = 0; % to initalise the total count display as 0
fullscreen = get(0,'ScreenSize');
figure('Position',[0 0 fullscreen(3) fullscreen(4)]);
for i = 11:20 % length(source)

    % read in frame
    start(vid);
    fr=getdata(vid);
    fr_bw = rgb2gray(fr); % convert frame to grayscale
    fr_diff = abs(double(fr_bw) - double(avebg));
    fr_diff=fr_diff/(max(max(fr_diff)));   % converted to single
    % cast operands as double to avoid negative overflow
    for j=1:width % if fr_diff > thresh pixel in foreground
        for k=1:height
            if ((fr_diff(k,j) > thresh))
                fg(k,j) = fr_bw(k,j);
            else
                fg(k,j) = 0;
            end
        end
    end
    bg_bw = fr_bw;
    subplot(2,2,1),imshow(fr_bw)
    title({'Input Video Sequence';[num2str(i) '-th frames']})
    subplot(2,2,2),imshow(uint8((fg>0).*255))
    title(['Detecting Human Object Using Thresholding'])
    fg_cleaned = bwareaopen(fg,5000);
    se = strel('square',50);
    Hpsf = fspecial('average', 15);
    fg_cleaned = imfilter(fg_cleaned,Hpsf,'symmetric');
    closeBW = imclose(fg_cleaned,se);
    subplot(2,2,3),imshow(closeBW)
    title(['Detecting Human Object Using Thresholding and Filtering'])
    closeBW2=uint8(closeBW).*fr_bw;
    subplot(2,2,4),imshow(closeBW2)
    M(i-1) = im2frame(uint8(fg_cleaned),gray); % put frames into movie
    L = bwlabel(closeBW);
    if i==11
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
    %% Boxing closeBW
    L = bwlabel(closeBW);
    [r, c] = find(L==1);
    top1=max(r);
    bottom1=min(r);
    right1=max(c);
    left1=min(c);
    width1=right1-left1;
    height1=top1-bottom1;
    Box1=[left1 bottom1 width1 height1];
    [r, c] = find(L==2);
    top2=max(r);
    bottom2=min(r);
    right2=max(c);
    left2=min(c);
    width2=right2-left2;
    height2=top2-bottom2;
    Box2=[left2 bottom2 width2 height2];
    %% Creating a rectangle
    if ~isempty(Box1)
        subplot(2,2,1)
        rectangle('Position',Box1,'EdgeColor','r');
    end
    if ~isempty(Box2)
        subplot(2,2,1)
        rectangle('Position',Box2,'EdgeColor','r');
    end
    pause(0.1);
end
