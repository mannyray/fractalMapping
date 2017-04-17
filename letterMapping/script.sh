#!/bin/bash

g++ -o conv -std=c++11 converter.cc
g++ -o map -std=c++11 map_image.cc ../compareImages.cc ../blockImage.cc
mkdir -p data
var=1
for file in movie/*.png
do
	echo $var
	convert "$file"  ${file%.*}.pgm
	./conv  ${file%.*}.pgm ${file%.*}.pnm
	./map ${file%.*}.pnm  "${file%.*}new.pnm"
	convert  "${file%.*}new.pnm" "data/$var.png" 
	var=$((var+1)) 
	
done
