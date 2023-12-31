function lab_09()
    I=double(imread('bimage18.bmp')) / 255;

    figure;
    imshow(I); 
    title('Source image');

    PSF=fspecial('disk', 1);
    J1=deconvblind(I, PSF);
    figure;
    imshow(J1);
    title('Recovered image'); 
end