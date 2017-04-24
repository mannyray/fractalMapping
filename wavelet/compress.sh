#!/bin/bash

#script designed to take image as input:
#1.Compute the wavelet decomposition  
#2.Come up with mappings in the wavelet decomposition trees



level_count=6
if [ "$#" -ne 1 ]; then
    echo "Illegal number of parameters. Please provide image file (example: lenna.pnm)"
		exit
fi


imageNameWithExtension=${1##*/}
imageName=${imageNameWithExtension%.*}


mkdir -p "$imageName"
#1.
#program creates wavelet decomposition into a.txt h.txt v.txt d.txt
matlab -r "createMappings $1 $level_count";



#organize .txt files into appropriate folders
mkdir -p "$imageName/d"
mv d.txt "$imageName/d"

mkdir -p "$imageName/a"
mv a.txt "$imageName/a"

mkdir -p "$imageName/h"
mv h.txt "$imageName/h"

mkdir -p "$imageName/v"
mv v.txt "$imageName/v"

#2.
g++ -o compress -std=c++11 wavelet.cc ../blockImage.cc ../compareImages.cc
./compress $level_count "$imageName/v/v.txt" "$imageName/v/mapping.txt"
./compress $level_count "$imageName/d/d.txt" "$imageName/d/mapping.txt"
./compress $level_count "$imageName/h/h.txt" "$imageName/h/mapping.txt"

