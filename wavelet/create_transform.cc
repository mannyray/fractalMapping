#include <iostream>
#include <string>
#include <fstream>
#include <math.h> 
#include <sstream>
#include <cstdint>
#include <limits>
#include <cstddef>

#include "../blockImage.h"
#include "waveletCompression.h"
//#include "regularFractalMappingWithRotate.h"


using namespace std;


int main(int argc, char *argv[]){
	/*
	goal is to read in the smallest level matrix and the 'tree'
	and follow the steps of expansion for it outward to create the bigger matrices
	and store in appropriate format for matlab to read in and create original image from
	*/
	
	if ( argc != 4 ){
    	cout<<"usage: "<< argv[0] << " <compressed_file> <level> <outputfile>\n";
    	return -1;
	}
	
	string file_name = argv[1];
	ifstream infile(file_name.c_str());
	
	string count_str = argv[2];
	stringstream ss(count_str);
	int level; ss>>level;
	int blockDimension =1;
	
	stringstream sss(argv[3]);
	string output_extension = sss.str();	
	ofstream ofile(output_extension);
	
	//blockDimension
	blockImage * firstMatrix = new blockImage(blockDimension);//blockMaps, mapStore, indexDataCount
	firstMatrix->readMatrixPNM(infile);
	
	
	int blockCount = firstMatrix->getBlockCount();
	
	
	//read in and store the mappings
	waveletCompression ** mappings = new waveletCompression*[level-1];
	for(int i = 0; i < level - 1; i++){
		mappings[i] = new waveletCompression(blockCount,4,2);
		mappings[i]->readMapping(infile, blockCount);
	}
	
	//write the first-first matrix to file
	firstMatrix->writeRoundOFF(true);
	firstMatrix->writeMatrixPNM(ofile);
	
	//execute the mappings
	for(int i = 0; i < level-1; i++){
				
		//define second imageblock
		blockImage * secondMatrix = new blockImage(blockDimension*2);
		//give it proper dimensions
		secondMatrix->makeEmpty(firstMatrix->getBlockRowCount(), firstMatrix->getBlockRowCount(),firstMatrix->getType());
	
		//expand the first image (making the dimensions match up)
		firstMatrix->expand();
		
	
		//map first to second 
		mappings[i]->map(firstMatrix,secondMatrix);
		
		//write second matrix to file
		secondMatrix->writeRoundOFF(true);
		secondMatrix->writeMatrixPNM(ofile);
		
		
		
		//switch pointers - the second matrix now becomes the first
		//delete the original first matrix
		blockImage * tmp = firstMatrix;
		firstMatrix = secondMatrix;
		delete tmp;
		
		//update blockDimension
		blockDimension *=2;
	}
	
	ofile.close();
	//clear up memory
	
	
}
