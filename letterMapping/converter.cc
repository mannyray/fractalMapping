#include <iostream>
#include <string>
#include <fstream>
#include <math.h> 
#include <sstream>
#include <cstdint>
#include <limits>
#include <cstddef>



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
	
	string output_file = argv[2];
	ofstream ofile(output_file.c_str());
	



	
	
	string type;
	int d1,d2,d3;
	infile>>type;ofile<<"P2"<<" ";
	infile>>d1;ofile<<d1<<" ";
	infile>>d2;ofile<<d2<<" ";
	infile>>d3;ofile<<d3<<endl;;
	getline(infile,type);
	
	char c = '3';
	while(infile.get(c)){
		unsigned char d = (unsigned char)c;
		ofile<<((int )d )<<endl;
	}
	
	
	
	ofile.close();
	
}
