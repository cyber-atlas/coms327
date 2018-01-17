#include <stdio.h>
#include<stdlib.h>
#define ROWCOL 8

int board[8][8];
void printSolution();//prints the current solution
void reset();//sets everything on the board to 0
int solution =0;//Saves the nubmer of sultions that work that we have found
void unmark(int row, int col);
void mark(int row, int col);
int charSelect[9] ={'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g','h'};//Used to find the corresponding character. 9 indeces because I initially forgot to account for the 0th space 

int main (){
	//When the program starts, everything is set to 0
	reset();
	//Loops through the board placing the initial queen at ecah location on the board then looking for other solutions based on the placement of the initial queen
//TODO need 8 nested rows

	//row 1 loop
	for (int first =0; first < 8; first++){
		if (board[0][first] == 0){
			mark(0, first);
		//	printf("%d",board[0][first]);
		//printSolution();
		//usleep(1000000000000);
		//second row loop

		for (int second =0; second < 8; second ++){
			
			if (board[1][second] == 0){
				mark (1, second);

			for (int third =0; third < 8; third++){

				if (board[2][third] == 0){
					mark(2, third);

				for (int fourth =0; fourth < 8; fourth++){

					if (board[3][fourth] == 0){
						mark(3, fourth);

					for (int fifth =0; fifth < 8; fifth++){

						if (board[4][fifth]==0){
							mark(4, fifth);

						for (int sixth =0; sixth < 8; sixth++){
							if (board[5][sixth]==0){
								mark(5, sixth);

							for (int seventh =0; seventh < 8; seventh++){
								if (board[6][seventh]==0){
								mark(6, seventh);

								for (int eigth =0; eigth < 8; eigth++){
									if (board[7][eigth]==0){
									mark(7, eigth);
								
									//Print all the Solutions
									printf("%d ,%c, %d, %c,  %d, %c, %d, %c, %d, %c, %d, %c, %d, %c, %d, %c, %d \n",solution,charSelect[1],first,charSelect[2],second, charSelect[3], third, charSelect[4], fourth, charSelect[5], fifth, charSelect[6], sixth, charSelect[7], seventh, charSelect[8], eigth);
									solution++;
								if (solution ==95){return 0;}
								unmark(7, eigth);
									}

								}//closes the 8th loop
							unmark(6, seventh);}
							}//closes the 7th loop
						unmark(5, sixth);}
						}//closes 6th loop
					unmark (4, fifth);}
					}//closes 5th loop
				unmark(3, fourth);}
				}//closes fourth loop
			unmark(2, third);}
				}//closes third loop 
		unmark (1, second);}
		}//closes 2nd loop

	unmark(0, first);
}

}//closes first loop
return 0;}

void mark(int row, int col ){

	board[row][col] = board[row][col] +1;

	for(int i =0; i < 8; i++){
		board[i][col] = board[i][col]+1;
}
	//Sets the row to notusble
	for (int i =0; i < 8; i++){
		board[row][i] = board[row][i]+1 ;
}

	//Checks each to make sure the number is in bounds and makes sure that it does not hit a NULL character (which woudl be outside the array)

	//Checks the quadrant 4 diagonal
	for(int i = row,j = col; j<8 && i<8; i++,j++ ){

		board[i][j] = board[i][j]+1;
	}
	//Checks the quadrant 3 diagonal
	for(int i = row,j = col; j>0 && i<8;  i++,j-- ){

		board[i][j] = board[i][j]+1;
	}
	//Checks quadrant 1 diagonal
	for(int i = row,j = col; j<8 && i>0 ; i--,j++ ){

		board[i][j] = board[i][j]+1;
	}
	//Checks quadrant 2 diagonal
	for(int i = row,j = col; j>0 && i>0; i--,j-- ){

		board[i][j] = board[i][j]+1;
	}


}



void unmark(int row, int col ){

	for(int i =0; i < 8; i++){
		board[i][col] = board[i][col]-1;
}
	//Sets the row to notusble
	for (int i =0; i < 8; i++){
		board[row][i] = board[row][i]-1 ;
}

	//Checks each to make sure the number is in bounds and makes sure that it does not hit a NULL character (which woudl be outside the array)
	
	board[row][col] = board[row][col]-1;	

	//Checks the quadrant 4 diagonal
	for(int i = row,j = col; j<8 && i<8; i++,j++ ){

		board[i][j] = board[i][j]-1;
	}
	//Checks the quadrant 3 diagonal
	for(int i = row,j = col; j>0 && i<8 ;  i++,j-- ){

		board[i][j] = board[i][j]-1;
	}
	//Checks quadrant 1 diagonal
	for(int i = row,j = col; j<8 && i>0  ; i--,j++ ){

		board[i][j] = board[i][j]-1;
	}
	//Checks quadrant 2 diagonal
	for(int i = row,j = col; j>0 && i>0 ; i--,j-- ){

		board[i][j] = board[i][j]-1;
	}


}


//TODO make a function to print the board so that it is easier to check
//TODO make a function that print the mark and unmark, sutff so that we can test that

void printSolution(){
	printf("\n");
	for(int i =0; i < 8; i++){
		for (int j =0; j<0; j++){
			printf ("%d", board[i][j]);
		}
 printf("\n");

}

}

void reset(){
	//Loops through and resets the board to 0
	for (int i=0; i < 8; i++){
		for (int j=0; j<8; j++){
			board[i][j] = 0;

		}
	}
}
