function  recreateWaveletImage(filename)
	fileID = fopen(filename,'r');
	formatSpec = '%f';
	C_m = fscanf(fileID,formatSpec);
	fclose(fileID);

	S = [   
        8 8 ;
        8 8;
		 16 16;
      %   32 32;
		 32    32;
		 64    64;
		128   128;
		256   256;
		512   512 ];


	Y = waverec2(C_m,S,'haar');
	Y = round(Y);
	%image(Y);
	%colormap gray(255);
	imwrite(Y,gray(255),'result.png')
	exit
end
