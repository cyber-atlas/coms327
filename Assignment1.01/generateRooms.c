#include <stdio.h>
#include <stdlib.h>

#define ROCK ' '
#define ROOMFLOOR '.'
#define CORRIDORFLOOR '#'
 
char dungeon[21][80];
int roomCount=0;

void border();
void printer();
void createRoom();

//generates a random number between 5 and 10 for the number of rooms
int numRooms = rand() % 6 +5;
//struct array to hold the number of rooms hard coded at 10 rooms as the max. 
struct room r[10]; 
//Variable to hold the number of the room that we are currently on starts with room 0
int roomNum =0;
	


//TODO Make a room adder to add 

//TODO make a way to check to make sure that rooms do not overlap
void checker(int roomNum ){
	if (dungeon[Rooms[roomNum].y][Rooms[roomnum].x] != '\0'){
	
		
	}



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
	for (int i =0; i < 21; i++){
		for (int j=0; j < 80; j++){
			printf("%c", dungeon[i][j]);
		}
		
		printf("\n");
	}
}



int main(){

	border();
	printer();


	srand(time(NULL));
	
	//Struct to hold the height, width and x and y position of the room
	struct room {
	
		int x;
		int y; 
		int w; 
		int h;
	}
	
	return 0;

}

//Generates the start of the room
void createRoom(){


	//generates a random number between 5 and 10 for the number of rooms
	int numRooms = rand() % 6 +5;
 	//struct array to hold the number of rooms hard coded at 10 rooms as the max. 
	struct room r[10]; 
	//Variable to hold the number of the room that we are currently on 	
	int roomNum =0;
	

	r[roomNum] = {
		r[roomNum].x  = rand() % 75 + 1;
		r[roomNum].y = rand() % 19 + 1;
		//Decided to limit the size of the room to 15
		r[roomNum].w = rand() % 12 + 3; 
		r[roomNum].h = rand() % 13 + 2;
	} 



	//TODO make and array with the randomly generated number of elements. Each element is room struct. 
	//Need have a varaible that tracks the number of rooms your are using for looping over the array, just hard code 10;
	//TODO structs don't need variables beacuase they are saved in array location.  
	//Need to find a way to store xpos ypos xlength ylength	
	//x needs length needs to be a minimum of 3 units, so start it away from the border, on the left and at least 3 units away on the right
	
	
	
	/*
	
	//TODO find out max size for x and y lengths, just pick reasonable size for upper limits ont that stuff.
	//Rooms must be at least 3 units long in the x direction
	int xlen = rand() +3;
	//Rooms must be at least 2 units long in the y direction
	int ylen = rand() + 2;
	
	*/
}

//After running through the checks, this will be called to add the room to the dungeon
void roomAdder(){
	
	dungeon[
}
		

}
