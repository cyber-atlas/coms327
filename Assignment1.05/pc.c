#include <stdlib.h>
#include <ncurses.h>

#include "string.h"

#include "dungeon.h"
#include "pc.h"
#include "utils.h"
#include "move.h"
#include "path.h"
#include "npc.h"


void pc_delete(pc_t *pc)
{
  if (pc) {
    free(pc);
  }
}

uint32_t pc_is_alive(dungeon_t *d)
{
  return d->pc.alive;
}

void place_pc(dungeon_t *d)
{
  d->pc.position[dim_y] = rand_range(d->rooms->position[dim_y],
                                     (d->rooms->position[dim_y] +
                                      d->rooms->size[dim_y] - 1));
  d->pc.position[dim_x] = rand_range(d->rooms->position[dim_x],
                                     (d->rooms->position[dim_x] +
                                      d->rooms->size[dim_x] - 1));
}

void config_pc(dungeon_t *d)
{
  memset(&d->pc, 0, sizeof (d->pc));
  d->pc.symbol = '@';

  place_pc(d);

  d->pc.speed = PC_SPEED;
  d->pc.alive = 1;
  d->pc.sequence_number = 0;
  d->pc.pc = calloc(1, sizeof (*d->pc.pc));
  d->pc.npc = NULL;
  d->pc.kills[kill_direct] = d->pc.kills[kill_avenged] = 0;

  d->character[d->pc.position[dim_y]][d->pc.position[dim_x]] = &d->pc;

  dijkstra(d);
  dijkstra_tunnel(d);
}

uint32_t pc_next_pos(dungeon_t *d, pair_t dir)
{
  dir[dim_y] = dir[dim_x] = 0;
	
  	int input;
	int conti=1;

	nodelay(stdscr, TRUE);
  do{
	switch(input = getch()){
		case '7':
		case 'y':
			dir[dim_y] = -1;
			dir[dim_x]= -1;
			conti =0;
			break;
		case'8':
		case 'k':
			dir [dim_y] =-1;
			conti =0;
			break;
		case'9':
		case'u':
			dir [dim_y] = -1;
			dir [dim_x] =+1;
			conti=0;
			break;
		case'6':
		case'l':
			dir[dim_x]=+1;
			conti=0;
			break;
		case '3':
		case'n': 
			dir[dim_y] =+1;
			dir[dim_x] =+1;
			conti=0;
			break;
		case '2':
		case 'j':
			dir[dim_y] = +1;
			conti=0;
			break;

		case '1':
		case 'b':
			dir[dim_y] = 1;
			dir[dim_x] = -1;
			conti = 0;
			break;
		case '4':
		case 'h':
			dir[dim_x] = -1;
			conti = 0;
			break;
		case '5':
		case ' ':
			dir[dim_y] = 0;
			dir[dim_x] = 0;
			conti = 0;
			break;
		case '>':

			if ((d->rooms->position[dim_x] == d->pc.position[dim_x]) && (d->rooms->position[dim_y] == d->pc.position[dim_y])) {
				delete_dungeon(d);
				init_dungeon(d);
				gen_dungeon(d);
				config_pc(d);
				gen_monsters(d);
				render_dungeon(d);
			}
			break;
		case '<':
			if ((d->rooms->position[dim_x] == d->pc.position[dim_x]) && (d->rooms->position[dim_y] + 1 == d->pc.position[dim_y])) {
				delete_dungeon(d);
				init_dungeon(d);
				gen_dungeon(d);
				config_pc(d);
				gen_monsters(d);
				render_dungeon(d);
			}
			break;
			//TODO look at how to fix the quit
		case 'Q':
			endwin();
			conti = 0;
			break;
		case 'm':
			//monster_list(d);
			break;
		default:
			continue;

	}

  } while (conti);


  return 0;
  		
	}
  
  
  

uint32_t pc_in_room(dungeon_t *d, uint32_t room)
{
  if ((room < d->num_rooms)                                     &&
      (d->pc.position[dim_x] >= d->rooms[room].position[dim_x]) &&
      (d->pc.position[dim_x] < (d->rooms[room].position[dim_x] +
                                d->rooms[room].size[dim_x]))    &&
      (d->pc.position[dim_y] >= d->rooms[room].position[dim_y]) &&
      (d->pc.position[dim_y] < (d->rooms[room].position[dim_y] +
                                d->rooms[room].size[dim_y]))) {
    return 1;
  }

  return 0;
}
