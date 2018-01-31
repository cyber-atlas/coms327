#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROCK ' '
#define ROOMFLOOR '.'
#define CORRIDORFLOOR '#'



	//Struct to hold the height, width and x and y position of the room
	//Follow this syntax for structs
	//reference by calling it room and
	typedef	struct room {

		int x;
		int y;
		int w;
		int h;
	}room;



char dungeon[21][80];
char hardness[21][80];

//struct array to hold the number of rooms hard coded at 10 rooms as the max.
struct room r[10];
//Variable to hold the number of the room that we are currently on starts with room 0
int roomNum =0;



//Checker should ensure the room fits in the dungeon
//Should also check to make sure make sure there is no overlap


int checker(int roomNum ){

	if ((r[roomNum].x + r[roomNum].w >80) || (r[roomNum].y + r[roomNum].h >20)){
		return 0;
	}
	for (int x = r[roomNum].x; x < r[roomNum].x + r[roomNum].w; x++){

		for (int y = r[roomNum].y; y < r[roomNum].y + r[roomNum].h; y++){
			
			//Makes sure it is not placing another room on another room or on the buffer character. This ensure rooms aren't clobberred and thatthere is adequate space between them. 
			if (dungeon[y][x] == ROOMFLOOR || dungeon[y][x] == '*'){

				return 0;
			}
		}
	}

	return 1;

}

//Makes the top and bottom border of the dungeon.
void border(){

	for (int i =0; i < 80; i++){
		dungeon[0][i] = '-';
		dungeon[20][i] = '-';
		//
		if (i>0 && i<21){
			dungeon[i][0] ='|';
			dungeon[i][79] ='|';
		}
	}
}
 void initDung(){
	border();
	//Intializes all that is not border to a rock
	for (int j= 0; j < 21; j++){
		for(int i =0; i<80; i++){
			if (dungeon[j][i] != '-' && dungeon[j][i] != '|'){
			dungeon[j][i] = ROCK;
			}
		}

	}
}
//Prints the dundeon to std out at the current location
void printer(){
	for (int i =0; i < 21; i++){
		for (int j=0; j < 80; j++){
			//Gets rid of the buffer character so that dungeon prints correctly
			if (dungeon[i][j] == '*'){dungeon[i][j] = ROCK;}
			printf("%c", dungeon[i][j]);
		}

		printf("\n");
	}
}


//After running through the checks, this will be called to add the room to the dungeon
void roomAdder(int roomNum){


	//loop through and create the walls, for the room on the sides
	//loop through and cdreate the floors for the x+h
	//loop through and create the floor for x+ w


	int i=  r[roomNum].x;
	int j =  r[roomNum].y;

	for (j; j< (r[roomNum].y + r[roomNum].h); j++){
		for (i =r[roomNum].x; i< (r[roomNum].x + r[roomNum].w); i++){

			dungeon[j][i] = ROOMFLOOR;
			
			//Creates a buffer around the perimeter of the room to make sure that the next room does not spawn too close
			dungeon[r[roomNum].y-1][i] = '*';
			dungeon[j][r[roomNum].x-1] = '*';
			dungeon[r[roomNum].y + r[roomNum].h][i] ='*';
			dungeon[j][r[roomNum].x + r[roomNum].w] = '*';

	}
	


}

}



//Generates the start of the room
void createRoom(int numRooms){


	//Holds the number of times you tried to add a new room
	int tries = 0;

	while (tries < 2000 && roomNum < numRooms ){

		r[roomNum].x  = rand() % 75 + 1;
		r[roomNum].y = rand() % 19 + 1;
		//Decided to limit the size of the room to 15
		r[roomNum].w = rand() % 7 + 3;
		r[roomNum].h = rand() % 6 + 2;

		 if (checker(roomNum)) {
			tries = 0;
			roomAdder(roomNum);
			roomNum++;
			continue;
		}
		tries++;

	}


}

//Will be passing in the structs from the room array
void createCorridor(room a, room b){

	if (a.x > b.x){

		for(int i = a.x; i>b.x; i--){
			if (dungeon[a.y][i] != ROOMFLOOR){
				dungeon[a.y][i] = CORRIDORFLOOR;
			}
		}
	}

	else{

		for(int i = a.x; i<b.x; i++){
			if (dungeon[a.y][i] != ROOMFLOOR){
				dungeon[a.y][i] = CORRIDORFLOOR;
			}
		}

	}

	if (a.y > b.y){

		for(int i = a.y; i>b.y; i--){
			if (dungeon[i][b.x] != ROOMFLOOR){
     dungeon[i][b.x] = CORRIDORFLOOR;
		}
	}
}

	else{
		for(int i = a.y; i<b.y; i++){
      if (dungeon[i][b.x] != ROOMFLOOR){
	      dungeon[i][b.x] = CORRIDORFLOOR;
    }
		}

	}
}


//Generating the hardness of the rooms
void generateHardness(){

	for (int col =0; col <20 ; col++){
		for(int row =0; row < 81; row++){
			//If the space in the dungeon is a rock, then it generates a hardness from 1 to 254
			if(dungeon[col][row] == ROCK){
				hardness[col][row] = rand()%253+1;
				break;
			} 
			//If the space in the dungeon is a room or corridor it generates a hardness of 0 because there is not rock there
			else if (dungeon[col][row] == CORRIDORFLOOR || dungeon[col][row] == ROOMFLOOR){
				hardness[col][row] = 0;
				break;
			}
			//If the place in the dungeon is a border character, then it is immutable and has a hardness of 255
			else if (dungeon[col][row] == '-' || dungeon[col][row] == '|'){
				hardness[col][row] = 255;
				break;
			} 

		}
	
	}

}





int main(){


	initDung();

	srand(time(NULL));

	//struct array to hold the number of rooms hard coded at 10 rooms as the max.
	int numRooms = rand() % 6 +5;

	createRoom(numRooms);

	for (int i = 0; i < numRooms-1; i++){
		createCorridor(r[i], r[i + 1]);
	}
	border();
	printer();
	//Prints the values of each of the structs, used for testing and verification
	//Lea =0; ving it in because it could be useful later
//	for (int i = 0; i < numRooms; i++){
	//	printf("x%d, y%d, w%d, h%d \n", r[i].x, r[i].y, r[i].w, r[i].h );
//	}


	generateHardness();
	return 0;

}
//TODO deal with the hardness of the rocks when that works
