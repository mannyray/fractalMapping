#!/bin/bash

#script designed to take image as input:
#1.Compute the wavelet decomposition  
#2.Come up with mappings in the wavelet decomposition trees
#3.Execute the mappings to get a new 'fractal' wavelet decomposition
#4.Combine the fractal decompositions into one big array
#5.Derive the image

if [ "$#" -ne 1 ]; then
    echo "Illegal number of parameters. Please provide image file (example: lenna.pnm)"
		exit
fi

#create file directory where everything will be stored

imageNameWithExtension=${1##*/}
imageName=${imageNameWithExtension%.*}

mkdir -p "$imageName"
#1.
#program creates wavelet decomposition into a.txt h.txt v.txt d.txt
matlab -r "createMappings $1";

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
g++ -std=c++11 wavelet.cc ../blockImage.cc ../compareImages.cc
./a.out 6 "$imageName/v/v.txt" "$imageName/v/mapping.txt"
./a.out 6 "$imageName/d/d.txt" "$imageName/d/mapping.txt"
./a.out 6 "$imageName/h/h.txt" "$imageName/h/mapping.txt"


#3
g++ -std=c++11 create_transform.cc ../blockImage.cc ../compareImages.cc
./a.out "$imageName/v/mapping.txt" 6 "$imageName/v/new_v.txt"
./a.out "$imageName/d/mapping.txt" 6 "$imageName/d/new_d.txt"
./a.out "$imageName/h/mapping.txt" 6 "$imageName/h/new_h.txt"


#4
g++ -std=c++11 combineTransforms.cc
./a.out "$imageName/a/a.txt" "$imageName/h/new_h.txt"  "$imageName/v/new_v.txt" "$imageName/d/new_d.txt" "$imageName/combined.txt"

#5 doesn't quite work
