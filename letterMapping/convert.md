convert lll.jpeg RESULT.pgm

 g++ -std=c++11 converter.cc 
 
 ./a.out ../../../../sample.pnm sample.pnm
 
  g++ -std=c++11 map_image.cc ../compareImages.cc ../blockImage.cc
  
  ./a.out sample.pnm lenna_letter.txt
