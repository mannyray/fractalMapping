#ifndef MATRIX_H
#define MATRIX_H
#include <ostream>
#include <istream>
#include <string>
#include "compareImages.h"


/*
Class for storing and processing an pnm image
*/
class blockImage{
	/*
	stores image as a blockRowCount by blockColCount 
	of blocks where each block is blockDimension by blockDimension pixels	
	*/
	int blockDimension;
	int blockColCount;
	int blockRowCount;
	int blockCount;//blockRowCount * blockColCount
	
	std::string type;//PNM reading input/output data
	
	
	/*
	Method responsible for turning a blockDimension by blockDimension matrix stored as array 
	into a blockDimension/2 by blockDimension/2 matrix stored as an array. Method does this 
	by approximating each 2 by 2 block of elements in matrix down to one by one block by taking average value
	of the four pixels.

	array input and output storage is equivalent to reading matrix row by row, left to right.
	*/
	double * blurMatrix(double * matrix, int blockDimension);
	
	double * expandMatrix(double * matrix, int blockDimension);

	//stores the image in the specified block fashion
	double **blockStore;
	
	//rounding of pixels in blockImage to match the integer 0-255 range is ON for default
	bool round = true;
	
	friend class compareImages;
	
	public:
		//defines an array for matrix
		blockImage(int blockDimension);
		
		
		//reads in the input to fill the blockStore structure
		//same as the method before, but for double 
		void readMatrixPNM(std::istream &infile);
		
		
		/*
		Method for reading a matrix in from specified inputstream infile.
		The data read in, number by number is equivalent to reading matrix row by row 
		from left to right. However, the data is read in and stored in such a way that
		it represents a set of blockDimensionxblockDimension blocks that when put in the original
		matrix form blockRowCountxblockColCount blocks.

		For example:
		xybb
		azbb
		ccdd
		ccdd

		would be read in and stored as

		store = [A,B,C,D]

		where
		A = [x,y,a,z]

		likewise for B,C,D


		Requirements:
		store: has to be defined ahead of time with appropriate dimensions
		infile usually points to some PNM type file input.
		*/
		void writeMatrixPNM(std::ostream &ofile);
		
		//reduces all of the blockDimension by blockDimension blocks to 
		//blockDimension/2 by blockDimension/2
		void blur();
		
		//this method allows a user to define to empty blockStore of specified blockCount given that constructor
		//with dimension size has already been called (blockCount = blockRowCount * blockColCount)
		//should only ever be used when readMatrixPNM has not been yet called to avoid memeory leaks
		void makeEmpty(int blockRowCount, int blockColCount, std::string t);
		
		//destructor
		~blockImage();
		
		//getter methods
		int getBlockDimension();
		
		int getBlockColCount();
		
		int getBlockRowCount();
		
		int getBlockCount();
		
		std::string getType();
		
		//updates the blockStore to correct Dimension, but keeps same block Dimensions
		void updateMap(int blockDimension);
		
		//return the norm between two matrices
		//both need same blockDimension and blockCount
		double differenceNormalized(blockImage * bi);
		
		//rounding ON or OFF for writeMatrixPNM
		void writeRoundOFF(bool isItOFF);
		
		//expand a matrix --> the opposite of blur
		void expand();//doubles the blockDimension
		
};


#endif
