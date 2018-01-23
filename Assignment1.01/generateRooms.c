#include <stdio.h>
#include <stdlib.h>

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


//generates a random number between 5 and 10 for the number of rooms for testing purposes, this is 1 for now
int numRooms = 1;
//int numRooms = rand() % 6 +5;
//struct array to hold the number of rooms hard coded at 10 rooms as the max. 
struct room r[10]; 
//Variable to hold the number of the room that we are currently on starts with room 0
//put in main when made
int roomNum =0;
	



//Checker should ensure the room fits in the dungeon
//Should also check to make sure make sure there is no overlap


int checker(int roomNum ){
	
	if ((r[roomNum].x + r[roomNum].w >81) || (r[roomNum].y + r[roomNum].h)){
		return 1;
	}
	for (int x = r[roomNum].x; x < r[roomNum].x + r[roomNum].w; x++){

		for (int y = r[roomNum].y; y < r[roomNum].y + r[roomNum].h; y++){
			

			if (dungeon[y][x] == ROOMFLOOR){
				return 1;
			}
		}
	}
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



//Generates the start of the room
void createRoom(){


	//generates a random number between 5 and 10 for the number of rooms
//	int numRooms = rand() % 6 +5;
 	//struct array to hold the number of rooms hard coded at 10 rooms as the max. 
//	struct room r[10]; 
	//Variable to hold the number of the room that we are currently on 	
	int roomNum =0;
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
			roomNum++;
			tries = 0;
			continue;
			roomAdder(roomNum);
		}
		tries++;
	
	}

	
}

//After running through the checks, this will be called to add the room to the dungeon
void roomAdder(roomNum){
	

	//loop through and create the walls, for the room on the sides
	//loop through and cdreate the floors for the x+h
	//loop through and create the ceiling for x+ w
	
	int i=  r[roomNum].x; 
	int j =  r[roomNum].y;

	for (i; i< (r[roomNum].x + r[roomNum].w); i++){
	
		for (j; j< (r[roomNum].y + r[roomNum].h); j++){

			dungeon[i][j] = ROOMFLOOR;	
	
	}	 


}
		
}
//Will be passing in the structs from the room array
void createCorridor(room a, room b){
	
	if (a.x > b.x){
	
		for(int i = a.x; i>b.x; i--){
			dungeon[a.y][i] = CORRIDORFLOOR; 
		}
	}

	else{
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

	border();
	printer();


	srand(time(NULL));
	
	//createRoom();
	
	r[0].x =5;

	r[0].y =5;

	r[0].w =5;

	r[0].h =5;
/*
	r[1].x =5;

	r[1].y =5;

	r[1].w =5;

	r[1].h =5;
*/


	printf("%d, %d, %d, %d", r[0].x, r[0].y, r[0].w, r[0].h);

	roomAdder();
	createCorridor(r[0], r[1]);
	printer();
	return 0;

}

