#include <iostream>
#include <string>
#include <fstream>
#include <math.h> 
#include <sstream>
#include <cstdint>
#include <limits>
#include <cstddef>

#include "../blockImage.h"
#include "regularFractalMapping.h"

using namespace std;


int main(int argc, char *argv[]){
	//input parsing
	if ( argc != 3 ){
    	cout<<"usage: "<< argv[0] <<" <file_input.pnm> <output_extension>\n";
    	return -1;
	}//writes the case #n to output_extension_n.txt
	
	//no filename error handling
	string file_name = argv[1];
	ifstream infile(file_name.c_str());
	stringstream ss(argv[2]);
	string output_extension = ss.str();	

	int blockDimension = 8;
	//we will be storing our 8x8 pixel blocks as ordered arrays (from left to right, moving down)	
	//storing as chars for data efficiency (dount want to be storing the normalized version
	//as that would be a float and would require more memory
	blockImage blockStore(blockDimension);	
	blockStore.readMatrixPNM(infile);
	
	//for the 16 by 16's we are going to read the input once again
	//and then approximate it before we store
	//for each 'block row'
	ifstream infile2(file_name.c_str());
	blockImage sixteenBySixteenBlockStore(blockDimension*2);
	sixteenBySixteenBlockStore.readMatrixPNM(infile2);	
	sixteenBySixteenBlockStore.blur();//approximate each 16 by 16 with an 8 by 8
	
	//this structure is responsible for computing and storing the fractal mapping
	
	RegularFractalMapping compare(blockStore.getBlockCount(),4,2);	
	compare.findOptimalMapping(&sixteenBySixteenBlockStore, &blockStore);
	
	//output the compression mapping to file
	ofstream ofile(output_extension);
	compare.writeMapping(ofile);
	ofile.close();
}
