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
			

			if (dungeon[y][x] == ROOMFLOOR){

				return 0;
			}
		}
	}

//TODO make an unuable border around each room. Make sure to check for it when I check to make sure it is not part of the floor. 

	/*
	for (int x = r[roomNum].x-1; x < r[roomNum].x + r[roomNum].w+1; x++){

		for (int y = r[roomNum].y-1; y < r[roomNum].y + r[roomNum].h+1; y++){
			

			dungeon[r[roomNum].y-1][x] = '&';
			dungeon[r[roomNum].h+1][x] ='&';
			dungeon[y][r[roomNum].x-1] = '&';
			dungeon[y][r[roomNum].w+1] ='&';
		}
	}
	*/



	return 1;

}


 void initDung(){
	//Prints the top and bottom border of the dungeon. 
	for (int i =0; i < 80; i++){
		dungeon[0][i] = '-';
		dungeon[20][i] = '-';
		//
		if (i>0 && i<21){
			dungeon[i][0] ='|';
			dungeon[i][79] ='|';
		}
	}
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
	
		//	dungeon[j][i] = roomNum + 48;	
			dungeon[j][i] = ROOMFLOOR;
	
	}	 


}
		
}



//Generates the start of the room
void createRoom(int numRooms){


	//generates a random number between 5 and 10 for the number of rooms
//	int numRooms = rand() % 6 +5;
 	//struct array to hold the number of rooms hard coded at 10 rooms as the max. 
//	struct room r[10]; 
	//Holds the number of times you tried to add a new room
	int tries = 0;
	
	while (tries < 2000 && roomNum < numRooms ){
		
		r[roomNum].x  = rand() % 75 + 1;
		r[roomNum].y = rand() % 19 + 1;
		//Decided to limit the size of the room to 15
		r[roomNum].w = rand() % 7 + 3; 
		r[roomNum].h = rand() % 6 + 2;
		
	//	roomNum++;//for testing 
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
	/*
	int currx = a.x -1;
	int curry = a.y;
	while(1){
	if (currx < b.x){
		if (curry < b.y){
			//Tries taking a diagonal approach downwards towards Q4
			if (dungeon[curry+1][currx+1] != ROOMFLOOR){
				dungeon[curry++][currx++] = CORRIDORFLOOR;
				continue;
			}
		//stays at the same y value and just tries to move the x accross 	
			if (dungeon[curry][currx+1] == ROOMFLOOR){
				dungeon[curry][currx++] = CORRIDORFLOOR;
				continue;
			}
		}
		if (curry > b.y){
			//Tries taking a diagonal approach upwards towards Q1
			if (dungeon[curry-1][currx+1] != ROOMFLOOR){
				dungeon[curry--][currx++] = CORRIDORFLOOR;
				continue;
			}
		//stays at the same y value and just tries to move the x accross 	
			if (dungeon[curry][currx+1] == ROOMFLOOR){
				dungeon[curry][currx++] = CORRIDORFLOOR;
				continue;
			}
		}
	
	}
	if (currx > b.x){
		if (curry < b.y){
			//Tries taking a diagonal approach downwards towards Q4
			if (dungeon[curry+1][currx-1] != ROOMFLOOR){
				dungeon[curry++][currx--] = CORRIDORFLOOR;
				continue;
			}
		//stays at the same y value and just tries to move the x accross 	
			if (dungeon[curry][currx-1] == ROOMFLOOR){
				dungeon[curry][currx--] = CORRIDORFLOOR;
				continue;
			}
		}
		if (curry > b.y){
			//Tries taking a diagonal approach upwards towards Q1
			if (dungeon[curry-1][currx-1] != ROOMFLOOR){
				dungeon[curry--][currx--] = CORRIDORFLOOR;
				continue;
			}
		//stays at the same y value and just tries to move the x accross 	
			if (dungeon[curry][currx-1] == ROOMFLOOR){
				dungeon[curry][currx--] = CORRIDORFLOOR;
				continue;
			}
		}
	
	}

	if (currx == b.x){
		if (curry == b.y){
			break;
		}
		if(curry > b.y){
			if (dungeon[curry-1][currx] != ROOMFLOOR){
				dungeon[curry--][currx] = CORRIDORFLOOR;
				continue;
			}
		}
		if(curry < b.y){
			if (dungeon[curry+1][currx] != ROOMFLOOR){
				dungeon[curry++][currx] = CORRIDORFLOOR;
				continue;
			}
		}
	}

	break;
	}

*/
	if (a.x > b.x){
	
		for(int i = a.x; i>b.x; i--){
			dungeon[a.y][i] = CORRIDORFLOOR; 
		}
	}

	if (a.x<b.x){

		for(int i = a.x; i<b.x; i++){
			dungeon[a.y][i] = CORRIDORFLOOR; 
		}

	}
		
	if (a.y > b.y){
	
		for(int i = a.y; i>b.y; i--){
			dungeon[i][a.x] = CORRIDORFLOOR; 
		}
	}

	else{
		for(int i = a.y; i<b.y; i++){
			dungeon[i][a.x] = CORRIDORFLOOR; 
		}

	}
	

}
int main(){


	initDung();
	printer();


	srand(time(NULL));
	
	//struct array to hold the number of rooms hard coded at 10 rooms as the max. 
	int numRooms = rand() % 6 +5;

	createRoom(numRooms);
/*	
	r[0].x =5;

	r[0].y =5;

	r[0].w =5;

	r[0].h =5;
	r[1].x =5;

	r[1].y =5;

	r[1].w =5;

	r[1].h =5;
*/

//	printf("%d, %d, %d, %d", r[0].x, r[0].y, r[0].w, r[0].h);
	printer();
	for (int i = 0; i < numRooms-1; i++){
		createCorridor(r[i], r[i++]);
		printer();//only here for testing
	}
	printer();
	//Prints the values of each of the structs, used for testing
	for (int i = 0; i < numRooms; i++){
		printf("x%d, y%d, w%d, h%d \n", r[i].x, r[i].y, r[i].w, r[i].h );
	}


	return 0;

}
//TODO deal with the hardness of the rocks when that works
