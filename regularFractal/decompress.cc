#include <iostream>
#include <string>
#include <fstream>
#include <math.h> 
#include <sstream>
#include <cstdint>
#include <limits>
#include <cstddef>
#include <sstream>

#include "../blockImage.h"
#include "regularFractalMapping.h"

using namespace std;



int main(int argc, char *argv[]){
	if ( argc != 4 ){
    	cout<<"usage: "<< argv[0] <<" <compression_file> <starting_image_pnm> <image_output_name_extension>\n";
    	//assuming dimension match up between the compression_file and starting image
    	return -1;
	}
	
	
	//READ IN THE COMPRESSION FILE
	string compression_file = argv[1];
	ifstream infile1(compression_file.c_str());
	
	string file_name = argv[2];
	ifstream infile2(file_name.c_str());
	ifstream infile2_2(file_name.c_str());
	ifstream infile2_3(file_name.c_str());
	
	
	stringstream ss(argv[3]);
	string output_extension = ss.str();
	
	int blockDimension = 8;
	blockImage * blockStore = new blockImage(blockDimension);
	blockImage * blockStore2= new blockImage (blockDimension);
	blockImage * sixteen_by_sixteen = new blockImage(blockDimension*2);
	
	
	
	blockStore->readMatrixPNM(infile2);
	infile2.close();
	blockStore2->readMatrixPNM(infile2_2);
	infile2_2.close();
	sixteen_by_sixteen->readMatrixPNM(infile2_3);
	infile2_3.close();
	
	
	
	RegularFractalMapping alpha_beta(blockStore->getBlockCount(), 4, 2);
	alpha_beta.readMapping(infile1,blockStore->getBlockCount());
	

	int iterationCount = 1;	
	double norm = 0;
	do{
		sixteen_by_sixteen->blur();

		//go through alpha_beta_store alongside with blockStore2 (8*8)'s and map approximated_16s to blockStore2
		alpha_beta.map(sixteen_by_sixteen, blockStore2);
	
		iterationCount++;
		
		//output the input and read it in once again
		blockImage *tmp = blockStore;
		blockStore = blockStore2;
		blockStore2 = tmp;
		stringstream ss;
		blockStore->writeRoundOFF(true);
		blockStore->writeMatrixPNM(ss);//not the most efficient data transfer, but it works and keeps things simple for now
		sixteen_by_sixteen->updateMap(blockDimension * 2);
		sixteen_by_sixteen->readMatrixPNM(ss);//TODO modify blockDimension as a result from blur

		
	}while(iterationCount < 20 );
	
	blockStore2->writeRoundOFF(false);
	std::ostringstream oss;
	oss << output_extension <<".pnm";
	//if user wants it to be done
	ofstream ff(oss.str().c_str());
	blockStore2->writeMatrixPNM(ff);
	ff.close();
		

	
	
}
