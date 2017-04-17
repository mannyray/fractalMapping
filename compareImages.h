#ifndef COMPAREIMAGES_H
#define COMPAREIMAGES_H
#include <ostream>
#include <istream>
#include "blockImage.h"




class blockImage;


//class for finding optimal mapping between two sets of matrices
//that stored in blockStore format as explained in matrix.h
class compareImages{
	
	//the amount of block map stores
	int mapSize = 0;
	
	/*
	dimension of a single mapping (elements involved). The first element is usually reserved for 'error'
	measurement when comparing different mappings
	the middle portion are used for mapping variables (such as constants multiples and such)
	the last elements are reserved for indexing between block mappings
	*/
	int mapStore = 4;
	
	//the amount of numbers used to store index data and error data
	int indexDataCount = 0;
	
	//mappingData[mapSize][mapStore] mapSize maps of mapStore size each
	double **mappingData;
	
	//need this for output purposes when storing a mapping to file
	int blockDimension;
	int blockRowCount;
	int blockColCount;
	
	protected:
		//compute the difference norm between two matrices of blockDimension by blockDimension
		double differenceNorm(double* ar1, double * ar2, int blockDimension);
	
	
		//take the transpose of a blockDimension by blockDimension matrix stored in array format
		void rotateVector(double * vector, int blockDimension);
	
		//method used in finding optimal mapping between two matrices as defined in specific subclass
		virtual void mappingBetweenTwoMatrices(double * vec1, double * vec2, double * result_array,  int blockDimension) =0;
		
		//map one matrix to anothern given single mapping
		virtual void mapOneMatrixToAnother(double * vec1, double * vec2, double * mapArray, int blockDimension) =0;
		
		//getter methods:
		int getIndexData();
		
		int getMapStore();
		
		int getMapSize();
		
	
	public: 
		
		/*
		constructor
		blockMaps is the amount of the mappings
		mapStore is for 
		indexVaribleCount is for
		*/
		compareImages(int blockMaps, int mapStore, int indexVariableCount);//need to define mapStore here
	
		//method to write the data to file 
		void writeMapping(std::ostream &ofile);
		
		//method to read the data from file
		void readMapping(std::istream &ifile, int blockCount);
		
		//compare two images ~ virtual because different methods have different comparison techniques
		void findOptimalMapping( blockImage * from, blockImage * to );
		
		//apply mapping stored in mappingData from 'from' to 'to.
		void map(blockImage * from, blockImage * to);		
		
};



#endif
