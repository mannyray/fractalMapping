#!/bin/bash

#3.Execute the mappings to get a new 'fractal' wavelet decomposition
#4.Combine the fractal decompositions into one big array
#5.Derive the image


level_count=6

if [ "$#" -ne 1 ]; then
    echo "Illegal number of parameters. Please provide image directory (lenna)"
		exit
fi



#3
g++ -std=c++11 create_transform.cc ../blockImage.cc ../compareImages.cc -o decompress
./decompress "$1/v/mapping.txt" $level_count "$1/v/new_v.txt"
./decompress "$1/d/mapping.txt" $level_count "$1/d/new_d.txt"
./decompress "$1/h/mapping.txt" $level_count "$1/h/new_h.txt"


#4
g++ -std=c++11 combineTransforms.cc -o combine
./combine "$1/a/a.txt" "$1/h/new_h.txt"  "$1/v/new_v.txt" "$1/d/new_d.txt" "$1/combined.txt"  $level_count

#5
matlab -r "recreateWaveletImage $1/combined.txt $level_count";
