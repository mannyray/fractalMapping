#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

/*
Read in from the separate a/d/h/v and order the correctly in order to make it easier to put it back into image form
using matlab
*/

int main(int argc, char *argv[]){
	if ( argc != 7 ){
    	cout<<"usage: "<< argv[0] << " <a file> <h file> <v file> <d file> <outputfile> <level_count>\n";
    	return -1;
	}
	
	//the order is starting is from the smallest sized level going up where each level is
	// A_lvl | H_lvl | V_lvl | D_lvl
	
	//set up the input/output streams
	string file_name = argv[1];
	ifstream a_infile(file_name.c_str());
	file_name = argv[2];
	ifstream h_infile(file_name.c_str());
	file_name = argv[3];
	ifstream v_infile(file_name.c_str());
	file_name = argv[4];
	ifstream d_infile(file_name.c_str());
	
	
	string level_string = argv[6];
	stringstream num_converter(level_string);
	int level; num_converter>>level;
	
	
	stringstream sss(argv[5]);
	string output_extension = sss.str();
	
	
		
	ofstream ofile(output_extension);
	int dimension = 0;int garbage;double number;

	for(int i = 0; i < level; i++){
		a_infile>>garbage>>dimension>>dimension>>garbage;
		h_infile>>garbage>>dimension>>dimension>>garbage;
		v_infile>>garbage>>dimension>>dimension>>garbage;
		d_infile>>garbage>>dimension>>dimension>>garbage;
		double ** matrix  = new double *[dimension];
		for(int j = 0; j < dimension; j++){
			matrix[j] = new double[dimension];
		}
		
		
		if(i == 0){
			for(int j = 0; j < dimension; j++){
				for(int k = 0; k < dimension; k++){
					a_infile>>number;
					matrix[j][k] = number;
				}
			}
			for(int j = 0; j < dimension; j++){
				for(int k = 0; k < dimension; k++){
					ofile<<matrix[k][j]<<" ";
				}
			}
		}

		for(int j = 0; j < dimension; j++){
			for(int k = 0; k < dimension; k++){
				h_infile>>number;
				matrix[j][k] = number;
			}
		}
		for(int j = 0; j < dimension; j++){
			for(int k = 0; k < dimension; k++){
				ofile<<matrix[k][j]<<" ";
			}
		}
		

		for(int j = 0; j < dimension; j++){
			for(int k = 0; k < dimension; k++){
				v_infile>>number;
				matrix[j][k] = number;
			}
		}
		for(int j = 0; j < dimension; j++){
			for(int k = 0; k < dimension; k++){
				ofile<<matrix[k][j]<<" ";
			}
		}
		
		

		for(int j = 0; j < dimension; j++){
			for(int k = 0; k < dimension; k++){
				d_infile>>number;
				matrix[j][k] = number;
			}
		}
		for(int j = 0; j < dimension; j++){
			for(int k = 0; k < dimension; k++){
				ofile<<matrix[k][j]<<" ";
			}
		}
	
		
		
		for(int j = 0; j < dimension; j++){
			delete [] matrix[j];
		}
		delete [] matrix;
	}
	ofile.close();
	
		
	
}
