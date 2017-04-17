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


using namespace std;
/*
program is responsible for creating the wavelet compression file
for a d/h/v/a column at a time
*/
int main(int argc, char *argv[]){
	/*read in our input
	and store in an array of n*n blocks

	*/
	if ( argc != 4 ){
    	cout<<"usage: "<< argv[0] <<" <level_count> <input_wavelet_decomposition> <output_extension>\n";
    	return -1;
	}
	
	string file_name = argv[2];
	ifstream infile(file_name.c_str());
	
	string count_str = argv[1];
	stringstream ss(count_str);
	int level; ss>>level;
	int blockDimension =1;
	
	
	stringstream sss(argv[3]);
	string output_extension = sss.str();	
	ofstream ofile(output_extension);

	


	blockImage ** matrix_holder= new blockImage*[level];
	for(int i = 0; i < level; i++){
		blockImage * matrix = new blockImage(blockDimension);
		matrix->readMatrixPNM(infile);
		matrix_holder[i] = matrix;
		blockDimension*=2;
	}
	
	matrix_holder[0]->writeRoundOFF(true);
	matrix_holder[0]->writeMatrixPNM(ofile);
	
	
	//figure out the mappings
	waveletCompression ** mappings = new waveletCompression*[level-1];
	for(int i = 0; i < level-1; i++){
		//define mapping
		mappings[i] = new waveletCompression(matrix_holder[i+1]->getBlockCount(),4,2);
		
		//do the mapping
		matrix_holder[i]->expand();
		
		mappings[i]->findOptimalMapping(matrix_holder[i], matrix_holder[i+1]);
		
		//write mapping to file
		mappings[i]->writeMapping(ofile);
	}
	ofile.close();
	
	for(int i = 0; i < level - 1; i++){
		delete mappings[i];
	}
	for(int i = 0; i < level; i++){
		delete matrix_holder[i];
	}
	delete [] mappings;
	delete [] matrix_holder;
}
