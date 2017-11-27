#include <iostream> //cout
#include <fstream> //file
#include <vector> //push_back
#include <sstream> //sstream separete the line
#include <cstdlib> //atoi
	
using namespace std;


int vectorSum[1792]; // storing the number of the each sum (1792 is the max sum, because if each cell contains 256 the maximum sum is 1792 of a snake)
int iVectorSnakes[1792][7]; // storing x of the snakes
int jVectorSnakes[1792][7]; // storing y of the snakes

//READING A CSV FILE
vector <vector<int> > csvToMatrix(const char* fileName){
    ifstream file ( fileName ); 
    string value,line;
    vector <vector<int> > grid;
    vector <int> array;
    while ( file.good() )
    {
    	getline ( file, line, '\n');
    	stringstream row(line);
    	while(getline ( row, value, ',')){
    		array.push_back( atoi(value.c_str()) );
		}
		grid.push_back( array );
		array.clear();
    }
	return grid;
}

//recursive function to find all the snakes and store the sum. It will stop when 2 snakes with same sum are found.
void findSnakes(int i, int j, vector <vector<int> > grid ,  int iSnake[] = new int[7], int jSnake[] = new int[7], int lenghtSnake=0,   int sum=0, int lastCommand=0 ){
	
	if ( i < 0 || j < 0 || i >= grid.size() || j >= grid.size() ){ //testing if is a valid snake
		return;
	} else {
			lenghtSnake++;
			sum+= grid[i][j];
			enum myChoice { NONE = 0, LEFT = 1, RIGHT = 2, DOWN = 3 };
			iSnake[lenghtSnake-1]=i;
			jSnake[lenghtSnake-1]=j;
			
			if (lenghtSnake == 7){ //checking if is a 7 length snake
				vectorSum[sum]++;
				if (vectorSum[sum] > 1){
					
					//checking if is valid pair
					bool validPair = true;
					for(int ii=0; ii<7;ii++){
						for (int jj=0; jj<7; jj++){
							if( (iSnake[ii] == iVectorSnakes[sum][jj]) && (jSnake[ii] == jVectorSnakes[sum][jj]) ) 
								validPair = false;
						}
					}
					
					if(validPair){
						cout << "SUM:" <<sum<< endl;
						cout << "SNAKE A:" <<iVectorSnakes[sum][0]+1 << "," <<jVectorSnakes[sum][0]+1 << " - " <<iVectorSnakes[sum][1]+1 << "," <<jVectorSnakes[sum][1]+1 << " - " <<iVectorSnakes[sum][2]+1 << "," <<jVectorSnakes[sum][2]+1 << " - " <<iVectorSnakes[sum][3]+1 << "," <<jVectorSnakes[sum][3]+1 << " - " <<iVectorSnakes[sum][4]+1 << "," <<jVectorSnakes[sum][4]+1 << " - " <<iVectorSnakes[sum][5]+1 << "," <<jVectorSnakes[sum][5]+1 << " - " <<iVectorSnakes[sum][6]+1 << "," <<jVectorSnakes[sum][6]+1 << endl;
						cout << "SNAKE B:" <<iSnake[0]+1			 << "," <<jSnake[0]+1 			  << " - " <<iSnake[1]+1 			 << "," <<jSnake[1]+1 			 << " - " <<iSnake[2]+1 			 << "," <<jSnake[2]+1 			  << " - " <<iSnake[3]+1 			 << "," <<jSnake[3]+1 			  << " - " <<iSnake[4]+1 			 << "," <<jSnake[4]+1 			  << " - " <<iSnake[5]+1 			 << "," <<jSnake[5]+1 			  << " - " <<iSnake[6]+1 			 << "," <<jSnake[6]+1 			  << endl <<endl;
						exit(0); //interrupts the program if find a pair of snakes
					} 
					
					return;	
				
				} else {
					for(int c=0;c<7;c++) { //storing the cells of a snake
						iVectorSnakes[sum][c]=iSnake[c];
						jVectorSnakes[sum][c]=jSnake[c];
					}			
					return;	
				}
					
		} else {
			switch(lastCommand) {
   				case LEFT: {  
					findSnakes(i,j-1,grid,iSnake,jSnake,lenghtSnake,sum,LEFT); //left
					findSnakes(i+1,j,grid,iSnake,jSnake,lenghtSnake,sum,DOWN); //bot
            		break;
            	}
            	case RIGHT: {  
					findSnakes(i,j+1,grid,iSnake,jSnake,lenghtSnake,sum,RIGHT); //right
					findSnakes(i+1,j,grid,iSnake,jSnake,lenghtSnake,sum,DOWN); //bot
            		break;
            	}
            	case DOWN: {
            		findSnakes(i,j-1,grid,iSnake,jSnake,lenghtSnake,sum,LEFT); //left
					findSnakes(i,j+1,grid,iSnake,jSnake,lenghtSnake,sum,RIGHT); //right
					findSnakes(i+1,j,grid,iSnake,jSnake,lenghtSnake,sum,DOWN); //bot
            		break;
            	}
    			default: 
    				findSnakes(i,j-1,grid,iSnake,jSnake,lenghtSnake,sum,LEFT); //left
					findSnakes(i,j+1,grid,iSnake,jSnake,lenghtSnake,sum,RIGHT); //right
					findSnakes(i+1,j,grid,iSnake,jSnake,lenghtSnake,sum,DOWN); //bot
            		break;
             	break;
			}
		}
	}
}


int main(int argc, char* argv[]) {

	vector <vector<int> > grid = csvToMatrix(argv[1]);

//	//PRINTING THE GRID
//	for (int i = 0; i < grid.size(); i++){
//	   	for (int j = 0; j < grid[i].size(); j++){
//	       	cout <<"["<<i<<"]["<<j<<"]"<< grid[i][j] <<endl; 
//	   	}
//	}

	//iniclializing the sum vector (count the occurrences of each sum)
	for (int i = 0; i < 1792; i++){
		vectorSum[i]=0;
	}

	//STORING ALL THE SUMS/SNAKES OF EACH CELL(HEAD'S SNAKE)
	if (grid.size() > 6) { //checks if the grid is smaller than the size of the snake
		for (int i = 0; i < grid.size(); i++){
	    	for (int j = 0; j < grid[i].size(); j++){
				findSnakes(i,j,grid); 
	    	}
		}
	}
	
	cout << "FAIL" << endl; //it will be printed if don't find a pair of snakes

    return 0;
}

