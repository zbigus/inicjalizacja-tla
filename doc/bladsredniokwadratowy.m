close all
referencyjny=imread('clip_03_ref_gray.png');
filename='clip_03_had_200_06_20diff.png'
%referencyjny = imcrop(referencyjny,[29, 3 , 480, 585]);  
% clipy [29, 3 , 480, 585]
%fountain [0, 15 , 320, 211]
%pedestrians [11, 0 , 299, 240]
%imshow(referencyjny);
%i=0;
if i==7
    i=0;
    wynikmat=zeros(5,7);
end
i=i+1;
%alpha_a0.8
%alpha_a0.9
%alpha_a0.95
%alpha_a0.97
%alpha_a0.99
%mean
%median
%mog
porownywany=imread('clip_03_had_200_06_20.png');
%porownywany = imcrop(porownywany,[29, 3 , 480, 585]);

%imshow(porownywany);

referencyjnyadj=imadjust(referencyjny);
porownywanyadj=imadjust(porownywany);
podobienstwo=0.99
roznica=imabsdiff(porownywany,referencyjny);
roznicaabs=imabsdiff(porownywany,referencyjny);
roznicaprocent=roznicaabs./255;
imshow(roznicaabs)
imwrite(roznicaabs,filename,'png');
roznica_pot=roznica.^2;
blsredkwad=sum(sum(roznica_pot))/numel(roznica_pot)
pix_similar70=sum(sum(roznicaabs<(0.3)*255))/numel(roznicaabs)
pix_similar80=sum(sum(roznicaabs<(0.2)*255))/numel(roznicaabs)
pix_similar90=sum(sum(roznicaabs<(0.1)*255))/numel(roznicaabs)
pix_similar98=sum(sum(roznicaabs<(0.02)*255))/numel(roznicaabs)
pix_similar99=sum(sum(roznicaabs<(0.01)*255))/numel(roznicaabs)
% wektorwyn=[blsredkwad;pix_similar80;pix_similar90;pix_similar98;pix_similar99]
% wynikmat(:,i)=wektorwyn;
%%
% figure
% subplot(3,1,1)
% [countsref,ref]=imhist(referencyjny)
% countsref2=countsref/255/100;
% stem(ref,countsref2,'.')
% axis([0 255 0 max(countsref2)])
% subplot(3,1,2)
% [countspor,por]=imhist(porownywany)
% countspor2=countspor/255/100;
% stem(por,countspor2,'.')
% axis([0 255 0 max(countspor2)])
% subplot(3,1,3)
% roz=countsref-countspor;
% roz=abs(roz)/255/100
% stem(0:1:255,roz,'.')
% axis([0 255 0 max(roz)])