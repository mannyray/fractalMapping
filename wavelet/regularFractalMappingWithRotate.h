#ifndef REGULARFRACTALMAPPINGWITHROTATE_H
#define REGULARFRACTALMAPPINGWITHROTATE_H
#include <ostream>
#include <istream>
#include "../blockImage.h"
#include <cstdint>
#include <limits>
#include <cstddef>

class blockImage;



class RegularFractalMappingWithRotate: public compareImages{
	public:
	
		RegularFractalMappingWithRotate(int blockMaps, int mapStore, int indexDataCount) : compareImages::compareImages(blockMaps, mapStore, indexDataCount){}
	
		//method used in finding optimal mapping between two matrices as defined in specific subclass
		void mapOneMatrixToAnother(double * one, double * two, double * result_array,  int blockDimension){//TODO one & two in right order?
		
			//rotate the correct amount of times
			for(int i = 0; i < result_array[2]; i++){
				rotateVector(one, blockDimension);
			}
		
			for(int i = 0; i < blockDimension*blockDimension; i++){
				two[i] = one[i]*result_array[0] + result_array[1];
			}
			
			//always rotate back to original
			if(result_array[2] == 0){
				return;
			}
			for(int i = result_array[2]; i < 4; i++){
				rotateVector(one,blockDimension);
			} 
		}
		
		
		//map one matrix to anothern given single mapping
		void mappingBetweenTwoMatrices(double * x, double * y, double * mapArray, int blockDimension){
			double min_error =  std::numeric_limits<double>::max();
			double * vec1 = new double[blockDimension*blockDimension];
			
			double * map = new double[getMapStore() - getIndexData()];//size 3
			map[2] = 0;//the rotation bit
			
			for(int i = 0; i < 4; i++){
				//http://stackoverflow.com/questions/5083465/fast-efficient-least-squares-fit-algorithm-in-c
				int n = blockDimension*blockDimension;
				double   sumx = 0.0;                       
				double   sumx2 = 0.0;                
				double   sumxy = 0.0;                       
				double   sumy = 0.0;                      
				double   sumy2 = 0.0;         
	
				for(int i=0;i<n;i++){
					sumx  += x[i];       
					sumy	+= y[i];
					sumx2 += pow((x[i]),2);  
					sumxy +=x[i] * y[i];     
					sumy2 += pow((y[i]),2); 
				}
			
				double denom = (n * sumx2 - pow(sumx,2));
				
				map[0] = (n * sumxy  -  sumx * sumy) / denom;
				map[1] = (sumy * sumx2  -  sumx * sumxy) / denom;
				
				mapOneMatrixToAnother(x, vec1, map, blockDimension);
				
				double error = differenceNorm(y, vec1, blockDimension);
								
				if(min_error > error){
					min_error = error;
					mapArray[0] = map[0];
					mapArray[1] = map[1];
					mapArray[2] = i;
				}
				
				rotateVector(x,blockDimension);
			}
		
		}

};

#endif
