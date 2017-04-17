#include <iostream>
#include <string>
#include <fstream>
#include <math.h> 
#include <sstream>
#include <cstdint>
#include <limits>
#include <cstddef>

#include "../blockImage.h"
#include "../compareImages.h"
#include "singleFractalMap.h"

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
	
	
	
	ifstream infile2("letters.pnm");
	blockImage letterMap(blockDimension);
	letterMap.readMatrixPNM(infile2);	
	

	
	SingleFractalMapping compare(blockStore.getBlockCount(),2,2);	
	compare.findOptimalMapping(&letterMap, &blockStore);
	
	//output the compression mapping to file
	//ofstream ofile(output_extension);
	//compare.writeMapping(ofile);
	//ofile.close();
	
	
	//read in the file and reproduce the image
	//SingleFractalMapping mapOut(blockStore.getBlockCount(),2,2);	
	//ifstream infile3(output_extension);
	//mapOut.readMapping(infile3,blockStore.getBlockCount());
	
	compare.map(&letterMap, &blockStore);
	
	
	string output_file = argv[2];
	ofstream ofile2(output_file.c_str());
	
	blockStore.writeMatrixPNM(ofile2);
	ofile2.close();
	
	
}
