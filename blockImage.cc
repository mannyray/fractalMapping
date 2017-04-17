#include "blockImage.h"
#include <ostream>
#include <istream>
#include <iostream>
#include <math.h>

using namespace std;


void blockImage::readMatrixPNM(istream &infile){
	int width,height,data_range;
	infile>>type>>height>>width>>data_range;
	blockRowCount = (height/blockDimension); 
	blockColCount = (width/blockDimension);  
	blockCount =  blockColCount*blockRowCount;
	
	blockStore = new double * [blockCount];
	
	for(int i = 0; i < blockCount; i++){
		blockStore[i] = new double[blockDimension*blockDimension];
	}	

	//for each 'block row'
	for(int i = 0; i < blockColCount; i++){
		//each 'block row' consists of blockDimension number of pixel rows
		for(int j = 0; j< blockDimension; j++){
			//each 'block collumn' section within a row
			for(int k = 0; k < blockRowCount;k++){
				//each 'block collumn is blockDimension pixels wide
				for(int m = 0; m < blockDimension; m++){
					//populate the array correctly in order that it is read
						infile>>blockStore[i*blockRowCount + k][j*blockDimension + m];
				}
			}
		}
	}
}


void blockImage::writeMatrixPNM(ostream &out  ){
	//for each 'block row'
	out<<type<<"  " <<blockDimension*blockRowCount<<"  " <<blockDimension*blockColCount << "  255" <<endl;
	for(int i = 0; i < blockColCount; i++){
		
		//each 'block row' consists of blockDimension number of pixel rows
		for(int j = 0; j< blockDimension; j++){
			//each 'block collumn' section within a row
			for(int k = 0; k < blockRowCount;k++){
				//each 'block collumn is blockDimension pixels wide
				for(int m = 0; m < blockDimension; m++){
					//populate the array correctly in order that it is read
					if(round){
						int data = (int)(blockStore[i*blockRowCount + k][j*blockDimension + m]+ 0.5);
						if(data < 0){
							data = 0;
						}
						else if(data > 255){
							data = 255;
						}
						out<<data<<endl;
					}
					else{
						out<<blockStore[i*blockRowCount + k][j*blockDimension + m]<<endl;
					}
				}
			}
		}
	}	
}



double * blockImage::blurMatrix(double * target, int blockDimensionOriginal){
	int blockDimension = blockDimensionOriginal/2;
	double * a = new double[blockDimension*blockDimension];
	for(int i = 0; i < blockDimension; i++){
		for(int j = 0; j < blockDimension; j++){
			a[i*blockDimension + j]  = target[i*4*blockDimension + j*2]; 
			a[i*blockDimension + j]  +=target[i*4*blockDimension + j*2 + 1] ;
			a[i*blockDimension + j]  += target[(i*4+2)*blockDimension + j*2];
			a[i*blockDimension + j]  += target[(i*4+2)*blockDimension + j*2 + 1];
			a[i*blockDimension + j] /=4;
		}
	}
	return a;
}



blockImage::blockImage(int blockDimension):blockDimension(blockDimension){}


void blockImage::blur(){
	for(int i = 0; i < blockCount; i++){
		double * ap = blurMatrix(blockStore[i],blockDimension);
		delete [] blockStore[i];
		blockStore[i] = ap;
	}
	blockDimension/=2;
	//column count and row count should still stay the same
}

blockImage::~blockImage(){
	for(int i = 0; i < blockCount; i++){
		delete [] blockStore[i];
	}
	delete [] blockStore;
}


int blockImage::getBlockDimension(){
	return blockDimension;
}
		
int blockImage::getBlockColCount(){
	return blockColCount;
}

int blockImage::getBlockRowCount(){
	return blockRowCount;
}

int blockImage::getBlockCount(){
	return blockCount;	
}


double blockImage::differenceNormalized(blockImage * bi){
	//error condition parsing
	if(blockDimension!=bi->getBlockDimension()){
		return -1;
	}
	else if(blockColCount!=bi->getBlockColCount()){
		return -1;
	}
	else if(blockRowCount!=bi->getBlockRowCount()){
		return -1;
	}
	double sum = 0;
	for(int i = 0; i < blockCount; i++){	
		double blockSum = 0;
		for(int j = 0; j < blockDimension*blockDimension; j++){
			blockSum += pow(blockStore[i][j] - bi->blockStore[i][j],2);
		}
	}
	return sqrt(sum)/((double)blockDimension*blockDimension*blockRowCount*blockColCount);
}


void blockImage::updateMap(int bd){
	//delete the old
	blockDimension = bd; 
	for(int i = 0; i < blockCount; i++){
		delete [] blockStore[i];
		blockStore[i] = new double[bd*bd];
	}
}

void  blockImage::writeRoundOFF(bool isItOFF){
	round = !isItOFF;
}

double * blockImage::expandMatrix(double * matrix, int originalBlockDimension){
	int newDimension = originalBlockDimension*2;
	double * a = new double [newDimension*newDimension];
	for(int i = 0; i < originalBlockDimension; i++){
		for(int j = 0; j < originalBlockDimension; j++){
			a[i*4*originalBlockDimension + j*2] = matrix[i*originalBlockDimension + j];
			a[i*4*originalBlockDimension + j*2 + 1] = matrix[i*originalBlockDimension + j];
			a[(i*4+2)*originalBlockDimension + j*2] = matrix[i*originalBlockDimension + j];
			a[(i*4+2)*originalBlockDimension + j*2 + 1] = matrix[i*originalBlockDimension + j];
		}
	}
	return a;	
}

void blockImage::expand(){
	for(int i = 0; i < blockCount; i++){
		double * replacement = expandMatrix(blockStore[i],blockDimension);
		delete [] blockStore[i];
		blockStore[i] = replacement;	
	}
	blockDimension*=2;
}

void blockImage::makeEmpty(int brc, int blc, string t){
	type = t;
	blockRowCount = brc;
	blockColCount = blc;
	blockCount = blockColCount * blockRowCount;
	//memory leak potential. read blockImage.h for details
	blockStore = new double * [blockCount];
	for(int i = 0; i < blockCount; i++){
		blockStore[i] = new double[blockDimension*blockDimension];
	}	
}

string blockImage::getType(){
	return type;
}

