#include <stdio.h>
#define ROWCOL 8

int board[ROWCOL][ROWCOL]; 
int place(int row, int col);
void change(int row, int col);
void printSolution();
int numQueens =0;
int queenLocations[ROWCOL*2];
int solution =0;

int main (){
	
	for (int i= 0; i < ROWCOL; i++){ 
		for (int j =0; j < ROWCOL; j++){
			place(i, j);
			change(i, j);
			printSolution();
	} 
	}
	
	return 0;
}
//Loops throught the array, if it runs into a location that is open, puts a queen down returns 0. Return 1 means there are no open spaces on the board
int place(int row, int col){
	
	for (int i =row; i < ROWCOL; i++){
		for (int j=col; j< ROWCOL; j++){
			if (board[i][j] == 0){
				board[i][j] == 1;
				//had to make sure I used the 2* numqueens before I updated numQueens to make sure I am in the correct index
				queenLocations[2*numQueens] = i;
				queenLocations[2*numQueens+1] = j;
				numQueens++;
			 	change(i, j);
				return 0;	
			}
		}

	}
       return 1;	

}

//Changes the diagonals and the row and column to unusable characters (7) in the the array
void change(int row, int col){
 
	for(int i = 0;  i < ROWCOL; i ++){
		for(int j =0; j< ROWCOL; j++){
			if (i == row || j == col){
				board[i][j] = 7;
			}
		}				
	} 

	for(int i = row,j = col; j<ROWCOL, i<ROWCOL; i++,j++ ){
	
		board[i][j] = 7;
	}
	for(int i = row,j = col; j>0 && i<ROWCOL; i++,j-- ){
	
		board[i][j] = 7;
	}

	for(int i = row,j = col; j<ROWCOL && i>0; i--,j++ ){
	
		board[i][j] = 7;
	}
	for(int i = row,j = col; j>0 && i>0; i--,j-- ){
	
		board[i][j] = 7;
	}
}

void printSolution(){

	printf("%d", solution);
	//Need to revisit because this is not very portable
	int alpha[ROWCOL] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};	
	for (int i=0; i < ROWCOL*2; i+= 2){
		//I saved everything as row, col. Spec says print as col, row
		printf("%c%d", alpha[queenLocations[i+1]], queenLocations[i]);
	}	
	solution++;
	printf ("\n");
}
