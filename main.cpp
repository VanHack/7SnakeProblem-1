#include <iostream> //cout
#include <fstream> //file
#include <vector> //push_back
#include <sstream> //sstream separete the line
#include <cstdlib> //atoi
	
using namespace std;


int vectorSum[1792]; // 1792 max sum
int iVectorSnakesA[1792][7]; // x of the first snake
int jVectorSnakesA[1792][7]; // y of the first snake
int iVectorSnakesB[1792][7]; // x of the second snake
int jVectorSnakesB[1792][7]; // y of the second snake

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
					for(int c=0;c<7;c++) { //storing the cells of a second snake
						iVectorSnakesB[sum][c]=iSnake[c];
						jVectorSnakesB[sum][c]=jSnake[c];
					}	
					
					//checking if is valid pair
					bool validPair = true;
					for(int ii=0; ii<7;ii++){
						for (int jj=0; jj<7; jj++){
							if( (iVectorSnakesB[sum][ii] == iVectorSnakesA[sum][jj]) && (jVectorSnakesB[sum][ii] == jVectorSnakesA[sum][jj]) ) 
								validPair = false;
						}
					}
					
					if(validPair){
						cout << "SUM:" <<sum<< endl;
						cout << "SNAKE A:" <<iVectorSnakesA[sum][0]+1 << "," <<jVectorSnakesA[sum][0]+1 << " - " <<iVectorSnakesA[sum][1]+1 << "," <<jVectorSnakesA[sum][1]+1 << " - " <<iVectorSnakesA[sum][2]+1 << "," <<jVectorSnakesA[sum][2]+1 << " - " <<iVectorSnakesA[sum][3]+1 << "," <<jVectorSnakesA[sum][3]+1 << " - " <<iVectorSnakesA[sum][4]+1 << "," <<jVectorSnakesA[sum][4]+1 << " - " <<iVectorSnakesA[sum][5]+1 << "," <<jVectorSnakesA[sum][5]+1 << " - " <<iVectorSnakesA[sum][6]+1 << "," <<jVectorSnakesA[sum][6]+1 << endl;
						cout << "SNAKE B:" <<iVectorSnakesB[sum][0]+1 << "," <<jVectorSnakesB[sum][0]+1 << " - " <<iVectorSnakesB[sum][1]+1 << "," <<jVectorSnakesB[sum][1]+1 << " - " <<iVectorSnakesB[sum][2]+1 << "," <<jVectorSnakesB[sum][2]+1 << " - " <<iVectorSnakesB[sum][3]+1 << "," <<jVectorSnakesB[sum][3]+1 << " - " <<iVectorSnakesB[sum][4]+1 << "," <<jVectorSnakesB[sum][4]+1 << " - " <<iVectorSnakesB[sum][5]+1 << "," <<jVectorSnakesB[sum][5]+1 << " - " <<iVectorSnakesB[sum][6]+1 << "," <<jVectorSnakesB[sum][6]+1 << endl <<endl;
						exit(0); //interrupts the program if find a pair of snakes
					} 
					
					return;	
				
				} else {
					for(int c=0;c<7;c++) { //storing the cells of a snake
						iVectorSnakesA[sum][c]=iSnake[c];
						jVectorSnakesA[sum][c]=jSnake[c];
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

