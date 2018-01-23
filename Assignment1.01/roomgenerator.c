#include <stdio.h>
#include <time.h>
#include <stdlib.h>


char map[80][21];



typedef struct dung
{
    int x_pos;
    int y_pos;
    int width;
    int height;

} dung_t ;



void map_print()
{
    int i;
    int j;

    for(i= 0 ; i < 21; i ++)
      {
        for(j = 0 ; j < 80; j ++)
        {

            printf("%c", map[j][i]);
        }

        printf("\n");
    }

}


dung_t room_gen()
{
    dung_t room;
    room.x_pos = (rand() %78)+1;
    room.y_pos = (rand() % 19)+1;
    room.width = (rand() %3) + 3;
    room.height = (rand()%2) + 2;

    if(room.x_pos + room.width >= 78)
    {
        room.x_pos -= room.width;
    }
    if(room.y_pos + room.height >= 19)
    {
        room.y_pos -= room.height;
    }

    return room;
}




void room_print (dung_t room)
{
    int i;
    int j;

    int widthsize = (room.x_pos + room.width + 1);
    int heightsize = (room.y_pos + room.height + 1);
    for(i = room.x_pos; i < widthsize; i++)
    {
        for(j = room.y_pos; j < heightsize; j++)
        {
            map[i][j] = '.';
        }
    }

}


void cord_gen (dung_t one, dung_t two)
{


    int cenX_one = one.x_pos + (one.width/2);
    int cenY_one = one.y_pos + (one.height/2);
    int cenX_two = two.x_pos + (two.width/2);
    int cenY_two = two.y_pos + (two.height/2);

    if(cenX_one < cenX_two)
    {
        while(cenX_one < cenX_two)
        {
            if(map[cenX_one][cenY_one] == ' ')
            {
                map[cenX_one][cenY_one] = '#';
            }
            cenX_one ++;
        }

	if(cenY_one < cenY_two)
    {
        while(cenY_one < cenY_two)
        {
	  if(map[cenX_one][cenY_one] == ' ')
            {
                map[cenX_one][cenY_one] = '#';
            }
	  cenY_one++;
        }
    }
    else
    {

        while(cenY_one > cenY_two)
        {
            if(map[cenX_one][cenY_one] == ' ')
            {
                map[cenX_one][cenY_one] = '#';
            }

            cenY_one--;
        }
    }
}

    else
    {
        while(cenX_two < cenX_one)
        {

            if((map[cenX_two][cenY_two] == ' '))
            {

                map[cenX_two][cenY_two] = '#';
            }

            cenX_two++;
        }

        if(cenY_two < cenY_one)
        {
            while(cenY_two < cenY_one)
            {
                if(map[cenX_two][cenY_two] == ' ')
		  {
                    map[cenX_two][cenY_two] = '#';
                }
                cenY_two++;
            }
        }
        else
        {
            while(cenY_two > cenY_one)
            {
                if(map[cenX_two][cenY_two] == ' ' )
                {
                    map[cenX_two][cenY_two] = '#';
                }
                cenY_two--;
            }
        }
    }

}



void corridors (dung_t room[5])
{
    cord_gen(room[0], room[1]);
    cord_gen(room[1], room[2]);
    cord_gen(room[2], room[3]);
    cord_gen(room[3], room[4]);

}

int main(int argc,  char * argv[]) {
    int i;
    int j;
    int height;
    int width;
    srand(time(NULL));


    int a = 5;
    dung_t room[a];

    for(height = 0 ; height < 5; height ++)
    {
        room[height] = room_gen();
    }

    for(i =0;i < 21; i++)
    {

        for(j =0 ; j < 80; j++)
        {
            map[j][i] = ' ';
        }
    }


    for(width = 0 ; width < 5; width++)
    {
        room_print(room[width]);
    }
    corridors(room);
    map_print();

    return 0;
}
