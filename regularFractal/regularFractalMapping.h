#ifndef REGULARFRACTALMAPPING_H
#define REGULARFRACTALMAPPING_H
#include <ostream>
#include <istream>
#include "../blockImage.h"
#include "../compareImages.h"

class blockImage;



class RegularFractalMapping: public compareImages{
	public:
	
		RegularFractalMapping(int blockMaps, int mapStore, int indexDataCount) : compareImages::compareImages(blockMaps, mapStore, indexDataCount){}
	
		//method used in finding optimal mapping between two matrices as defined in specific subclass
		void mapOneMatrixToAnother(double * one, double * two, double * result_array,  int blockDimension){//TODO one & two in right order?
			for(int i = 0; i < blockDimension*blockDimension; i++){
				two[i] = one[i]*result_array[0] + result_array[1];
			}
		}
		
		//map one matrix to anothern given single mapping
		void mappingBetweenTwoMatrices(double * x, double * y, double * mapArray, int blockDimension){
			//http://stackoverflow.com/questions/5083465/fast-efficient-least-squares-fit-algorithm-in-c
			int n = blockDimension*blockDimension;
			double   sumx = 0.0;                       
			double   sumx2 = 0.0;                
			double   sumxy = 0.0;                       
			double   sumy = 0.0;                      
			double   sumy2 = 0.0;         
	
			for (int i=0;i<n;i++){
				sumx  += x[i];       
				sumy	+= y[i];
				sumx2 += pow((x[i]),2);  
				sumxy +=x[i] * y[i];     
				sumy2 += pow((y[i]),2); 
			}
			
			double denom = (n * sumx2 - pow(sumx,2));
			mapArray[0] = (n * sumxy  -  sumx * sumy) / denom;
			mapArray[1] = (sumy * sumx2  -  sumx * sumxy) / denom;
		}
		
		

};

#endif
