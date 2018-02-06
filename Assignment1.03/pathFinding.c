#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROCK ' '
#define ROOMFLOOR '.'
#define CORRIDORFLOOR '#'


#define DUNGEON_X              80
#define DUNGEON_Y              21
#define MIN_ROOMS              5
#define MAX_ROOMS              9
#define ROOM_MIN_X             4
#define ROOM_MIN_Y             2
#define ROOM_MAX_X             14
#define ROOM_MAX_Y             8


int PlayerX = 0;
int PlayerY = 0;




typedef int16_t pair_t[num_dims];

 #define DUNGEON_X              80
 #define DUNGEON_Y              21
 #define MIN_ROOMS              5
 #define MAX_ROOMS              9
 #define ROOM_MIN_X             4
 #define ROOM_MIN_Y             2
 #define ROOM_MAX_X             14
 #define ROOM_MAX_Y             8

 #define mappair(pair) (d->map[pair[dim_y]][pair[dim_x]])
 #define mapxy(x, y) (d->map[y][x])
 #define hardnesspair(pair) (d->hardness[pair[dim_y]][pair[dim_x]])
 #define hardnessxy(x, y) (d->hardness[y][x])



//Places the player randomly on the board
void placePlayer(){
	int playerPlaced =0;
	while (playerPlaced = 0){
		PlayerX = rand()%81;
		PlayerY = rand()%22;
		if dungeon[PlayerX][PlayerY] == ROOMFLOOR {
			dungeon[PlayerX][PlayerY]=='@';
			playerPlaced =1;
		}
	}

}


static void dijkstra_corridor(dungeon_t *d, pair_t from)
{
  static corridor_path_t path[DUNGEON_Y][DUNGEON_X], *p;
  //uint32_t is an unsigned 32 bit integer. Functions the same as an integer but you know exactly how big
  //Is a data type
  static uint32_t initialized = 0;
  heap_t h;
  uint32_t x, y;

  //Will always be not initialized, because it is initialized above
  if (!initialized) {
    for (y = 0; y < DUNGEON_Y; y++) {
      for (x = 0; x < DUNGEON_X; x++) {
        path[y][x].pos[dim_y] = y;
        path[y][x].pos[dim_x] = x;
      }
    }
    initialized = 1;
  }

  for (y = 0; y < DUNGEON_Y; y++) {
    for (x = 0; x < DUNGEON_X; x++) {
      path[y][x].cost = INT_MAX;
    }
  }

  path[from[dim_y]][from[dim_x]].cost = 0;

  heap_init(&h, corridor_path_cmp, NULL);

  for (y = 0; y < DUNGEON_Y; y++) {
    for (x = 0; x < DUNGEON_X; x++) {
      if (mapxy(x, y) != ter_wall_immutable) {
        path[y][x].hn = heap_insert(&h, &path[y][x]);
      } else {
        path[y][x].hn = NULL;
      }
    }
  }
//removes items from the heap
  while ((p = heap_remove_min(&h))) {
    p->hn = NULL;

 //Made the diagnals
    if ((path[p->pos[dim_y] - 1][p->pos[dim_x] -1 ].hn) &&
        (path[p->pos[dim_y] - 1][p->pos[dim_x]   -1 ].cost >
         p->cost + hardnesspair(p->pos))) {
      path[p->pos[dim_y] - 1][p->pos[dim_x]  -1  ].cost =
        p->cost + hardnesspair(p->pos);
      path[p->pos[dim_y] - 1][p->pos[dim_x]  -1  ].from[dim_y] = p->pos[dim_y];
      path[p->pos[dim_y] - 1][p->pos[dim_x]  -1  ].from[dim_x] = p->pos[dim_x];
      heap_decrease_key_no_replace(&h, path[p->pos[dim_y] - 1]
                                           [p->pos[dim_x] -1   ].hn);
    }
    if ((path[p->pos[dim_y] +1   ][p->pos[dim_x] - 1].hn) &&
        (path[p->pos[dim_y]  +1  ][p->pos[dim_x] - 1].cost >
         p->cost + hardnesspair(p->pos))) {
      path[p->pos[dim_y] +1   ][p->pos[dim_x] - 1].cost =
        p->cost + hardnesspair(p->pos);
      path[p->pos[dim_y] +1   ][p->pos[dim_x] - 1].from[dim_y] = p->pos[dim_y];
      path[p->pos[dim_y] +1   ][p->pos[dim_x] - 1].from[dim_x] = p->pos[dim_x];
      heap_decrease_key_no_replace(&h, path[p->pos[dim_y] +1   ]
                                           [p->pos[dim_x] - 1].hn);
    }
    if ((path[p->pos[dim_y] -1   ][p->pos[dim_x] + 1].hn) &&
        (path[p->pos[dim_y] -1   ][p->pos[dim_x] + 1].cost >
         p->cost + hardnesspair(p->pos))) {
      path[p->pos[dim_y] -1   ][p->pos[dim_x] + 1].cost =
        p->cost + hardnesspair(p->pos);
      path[p->pos[dim_y] -1   ][p->pos[dim_x] + 1].from[dim_y] = p->pos[dim_y];
      path[p->pos[dim_y] -1   ][p->pos[dim_x] + 1].from[dim_x] = p->pos[dim_x];
      heap_decrease_key_no_replace(&h, path[p->pos[dim_y] -1   ]
                                           [p->pos[dim_x] + 1].hn);
    }
    if ((path[p->pos[dim_y] + 1][p->pos[dim_x] +1   ].hn) &&
        (path[p->pos[dim_y] + 1][p->pos[dim_x] +1   ].cost >
         p->cost + hardnesspair(p->pos))) {
      path[p->pos[dim_y] + 1][p->pos[dim_x]  +1  ].cost =
        p->cost + hardnesspair(p->pos);
      path[p->pos[dim_y] + 1][p->pos[dim_x] +1  ].from[dim_y] = p->pos[dim_y];
      path[p->pos[dim_y] + 1][p->pos[dim_x] +1  ].from[dim_x] = p->pos[dim_x];
      heap_decrease_key_no_replace(&h, path[p->pos[dim_y] + 1]
                                           [p->pos[dim_x] +1  ].hn);
    }
//Makes it go in the cardinal directions

    if ((path[p->pos[dim_y] - 1][p->pos[dim_x]    ].hn) &&
        (path[p->pos[dim_y] - 1][p->pos[dim_x]    ].cost >
         p->cost + hardnesspair(p->pos))) {
      path[p->pos[dim_y] - 1][p->pos[dim_x]    ].cost =
        p->cost + hardnesspair(p->pos);
      path[p->pos[dim_y] - 1][p->pos[dim_x]    ].from[dim_y] = p->pos[dim_y];
      path[p->pos[dim_y] - 1][p->pos[dim_x]    ].from[dim_x] = p->pos[dim_x];
      heap_decrease_key_no_replace(&h, path[p->pos[dim_y] - 1]
                                           [p->pos[dim_x]    ].hn);
    }
    if ((path[p->pos[dim_y]    ][p->pos[dim_x] - 1].hn) &&
        (path[p->pos[dim_y]    ][p->pos[dim_x] - 1].cost >
         p->cost + hardnesspair(p->pos))) {
      path[p->pos[dim_y]    ][p->pos[dim_x] - 1].cost =
        p->cost + hardnesspair(p->pos);
      path[p->pos[dim_y]    ][p->pos[dim_x] - 1].from[dim_y] = p->pos[dim_y];
      path[p->pos[dim_y]    ][p->pos[dim_x] - 1].from[dim_x] = p->pos[dim_x];
      heap_decrease_key_no_replace(&h, path[p->pos[dim_y]    ]
                                           [p->pos[dim_x] - 1].hn);
    }
    if ((path[p->pos[dim_y]    ][p->pos[dim_x] + 1].hn) &&
        (path[p->pos[dim_y]    ][p->pos[dim_x] + 1].cost >
         p->cost + hardnesspair(p->pos))) {
      path[p->pos[dim_y]    ][p->pos[dim_x] + 1].cost =
        p->cost + hardnesspair(p->pos);
      path[p->pos[dim_y]    ][p->pos[dim_x] + 1].from[dim_y] = p->pos[dim_y];
      path[p->pos[dim_y]    ][p->pos[dim_x] + 1].from[dim_x] = p->pos[dim_x];
      heap_decrease_key_no_replace(&h, path[p->pos[dim_y]    ]
                                           [p->pos[dim_x] + 1].hn);
    }
    if ((path[p->pos[dim_y] + 1][p->pos[dim_x]    ].hn) &&
        (path[p->pos[dim_y] + 1][p->pos[dim_x]    ].cost >
         p->cost + hardnesspair(p->pos))) {
      path[p->pos[dim_y] + 1][p->pos[dim_x]    ].cost =
        p->cost + hardnesspair(p->pos);
      path[p->pos[dim_y] + 1][p->pos[dim_x]    ].from[dim_y] = p->pos[dim_y];
      path[p->pos[dim_y] + 1][p->pos[dim_x]    ].from[dim_x] = p->pos[dim_x];
      heap_decrease_key_no_replace(&h, path[p->pos[dim_y] + 1]
                                           [p->pos[dim_x]    ].hn);
    }
  }
    heap_delete(&h);

}

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

void generateRockHardness(){

	for (int i= 0; i < 21; i+1){


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
	placePlayer();
	printer();
	//Prints the values of each of the structs, used for testing and verification
	//Leaving it in because it could be useful later
//	for (int i = 0; i < numRooms; i++){
	//	printf("x%d, y%d, w%d, h%d \n", r[i].x, r[i].y, r[i].w, r[i].h );
//	}


	return 0;

}
