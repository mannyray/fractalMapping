#ifndef SINGLEFRACTALMAP_H     
#define SINGLEFRACTALMAP_H
#include <ostream>
#include <istream>
#include "../blockImage.h"
#include "../compareImages.h"

class blockImage;



class SingleFractalMapping: public compareImages{
	public:
	
		SingleFractalMapping(int blockMaps, int mapStore, int indexDataCount) : compareImages::compareImages(blockMaps, mapStore, indexDataCount){}
	
		//method used in finding optimal mapping between two matrices as defined in specific subclass
		void mapOneMatrixToAnother(double * one, double * two, double * result_array,  int blockDimension){//TODO one & two in right order?
			for(int i = 0; i < blockDimension*blockDimension; i++){
				two[i] = one[i];
			}
		}
		
		//map one matrix to anothern given single mapping
		void mappingBetweenTwoMatrices(double * x, double * y, double * mapArray, int blockDimension){
			
		}
		
		

};

#endif
