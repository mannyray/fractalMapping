#ifndef REGULARFRACTALMAPPINGWITHROTATE_H
#define REGULARFRACTALMAPPINGWITHROTATE_H
#include <ostream>
#include <istream>
#include "../blockImage.h"
#include <cstdint>
#include <limits>
#include <cstddef>

class blockImage;

class waveletCompression: public compareImages{
	public:
	
		waveletCompression(int blockMaps, int mapStore, int indexDataCount) : compareImages::compareImages(blockMaps, mapStore, indexDataCount){}
	
		//method used in finding optimal mapping between two matrices as defined in specific subclass
		void mapOneMatrixToAnother(double * one, double * two, double * result_array,  int blockDimension){//TODO one & two in right order?
		
			//rotate the correct amount of times
			if(result_array[1] != 0){
				for(int i = 0; i < result_array[1]; i++){
					rotateVector(one, blockDimension);
				}
			}
		
			for(int i = 0; i < blockDimension*blockDimension; i++){
				two[i] = one[i]*result_array[0];
			}
			
			//always rotate back to original
			if(result_array[1] == 0){
				return;
			}
			for(int i = result_array[1]; i < 4; i++){
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
			
				/*http://stackoverflow.com/questions/12495396/fitting-a-line-that-passes-through-the-origin-0-0-to-data
				  (x1*y1 + x2*y2  + ... xn*yn)
			a =  ----------------------------
				  (x1*x1 + x2*x2  + ... xn*xn)
			  */
			
			
				int n = blockDimension*blockDimension;
				double   sumx2 = 0.0;                
				double   sumxy = 0.0;                       

				for(int i=0;i<n;i++){
					sumx2 += pow((x[i]),2);
					sumxy +=x[i] * y[i];
				}
				
				map[0] = sumxy/sumx2;

				mapOneMatrixToAnother(x, vec1, map, blockDimension);
				
				double error = differenceNorm(y, vec1, blockDimension);
								
				if(min_error > error){
					min_error = error;
					mapArray[0] = map[0];
					mapArray[1] = i;
				}
				
				rotateVector(x,blockDimension);
			}
			delete [] map;
			delete [] vec1;
		
		}

};

#endif
