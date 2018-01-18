#include <stdio.h>
#

#define ROCK ' '
#define ROOMFLOOR '.'
#define CORRIDORFLOOR '#'
 
char dungeon[21][80];
int roomCount=0;

void border();
void printer();

int main(){

	border();
	printer();
	
	return 0;

}


void border(){
	//Prints the top and bottom border of the dungeon. 
	for (int i =0; i < 80; i++){
		dungeon[0][i] = '-';
		dungeon[21][i] = '-';
		//
		if (i>0 && i<21){
			dungeon[i][0] ='|';
			dungeon[i][79] ='|';
		}
	}
	
}
//Prints the dundeon to std out at the current location
void printer(){
	for (int i =0; i <= 21; i++){
		for (int j=0; j < 80; j++){
			printf("%c", dungeon[i][j]);
		}
		
		printf("\n");
	}
}
