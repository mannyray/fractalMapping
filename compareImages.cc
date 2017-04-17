#include "compareImages.h"
#include "blockImage.h"
#include <cstdint>
#include <limits>
#include <cstddef>
#include <ostream>
#include <istream>
#include <math.h>
#include <iostream>

using namespace std;

class blockImage;


double compareImages::differenceNorm(double* ar1, double * ar2, int blockDimension){
	double sum = 0;
	for(int i = 0; i < blockDimension * blockDimension; i++){
		sum+=pow((ar1[i]) - (ar2[i]),2);
	}
	sum = sqrt(sum/(blockDimension*blockDimension))/255.0;
	return sum;
}

void compareImages::rotateVector(double * vector, int blockDimension){
	//in memory rotation of matrix not implemented
	double **rows = new double*[blockDimension];
	int index = 0;
	for(int i = 0; i < blockDimension; i++){
		rows[i] = new double[blockDimension];
		for(int j = 0; j < blockDimension; j++){
			rows[i][j] = vector[index];
			index++;
		}
	}
	
	//time to do rotate
	for(int i = 0; i < blockDimension; i++){//column
		for(int j = 0; j < blockDimension; j++){//row
			vector[i*blockDimension + j] = rows[j][i];
		}
	}
	
	for(int i = 0; i < blockDimension; i++){
		delete [] rows[i];
	}
	delete [] rows;

}

compareImages::compareImages(int blockMaps, int mapStore, int indexDataCount):mapSize(blockMaps),mapStore(mapStore),indexDataCount(indexDataCount){
	mappingData = new double*[blockMaps];
	for(int i = 0; i < blockMaps; i++){
		mappingData[i] = new double[mapStore];
		for(int j = 0; j < mapStore; j++){
			//for comparison purposes later, if you are trying to come up with some sort of minimal mapping
			//then it makes sense to store some variables as worst case possible maxs values
			mappingData[i][j] = std::numeric_limits<double>::max();
		}
	}
}

void compareImages::writeMapping(std::ostream &ofile){
	ofile<<blockDimension<<" "<<blockColCount<<" "<<blockRowCount<<endl;
	for(int i = 0; i < mapSize; i++){
		for(int j = 1; j < mapStore; j++){
			ofile<<mappingData[i][j]<<" ";
		}ofile<<endl;
	}
}

void compareImages::readMapping(std::istream &ifile, int blockCount){
	mapSize = blockCount;
	ifile>>blockDimension>>blockColCount>>blockRowCount;
	for(int i = 0; i < mapSize; i++){
		for(int j = 1; j < mapStore; j++){//starts at 1 because 1 is usually kept as the min error holder from findOptimalMapping
			ifile>>mappingData[i][j];
		}
	}
}

void compareImages::findOptimalMapping( blockImage * from, blockImage * to ){
	blockDimension = to->getBlockDimension();
	blockRowCount = to->getBlockColCount();
	blockColCount = to->getBlockRowCount();
	
	double * dataArray = new double [blockDimension*blockDimension];
	
	double * mapArray = new double [mapStore - indexDataCount];
	for(int i = 0; i < from->blockCount; i++){	
		for(int j = 0; j < to->blockCount; j++){
			mappingBetweenTwoMatrices(from->blockStore[i], to->blockStore[j], mapArray, blockDimension);
			mapOneMatrixToAnother(from->blockStore[i],dataArray, mapArray, blockDimension);
			double error = differenceNorm(to->blockStore[j],dataArray, blockDimension);
			if(mappingData[j][0] > error){
				mappingData[j][0] = error;
				for(int k = 1; k < 1+ mapStore - indexDataCount; k++){
					mappingData[j][k] = mapArray[k-1];
				}
				mappingData[j][mapStore-1] = i;
			}
		}
	}
	delete [] mapArray;
	delete [] dataArray;
}

void compareImages::map(blockImage * from, blockImage * to){
	double * mapArray = new double [mapStore - indexDataCount];
	for(int i = 0; i < mapSize; i++){
		int index = (int)mappingData[i][mapStore-1];
		for(int j = 1; j < 1+ mapStore-indexDataCount; j++){
			mapArray[j-1] = mappingData[i][j];
		}
		mapOneMatrixToAnother(from->blockStore[index], to->blockStore[i], mapArray,  blockDimension);
	}
}


int compareImages::getIndexData(){
	return indexDataCount;
}

int compareImages::getMapStore(){
	return mapStore;
}

int compareImages::getMapSize(){
	return mapSize;
}


