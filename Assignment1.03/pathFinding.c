#include <stdio.h>


#define DUNGEON_X              80
#define DUNGEON_Y              21
#define MIN_ROOMS              5
#define MAX_ROOMS              9
#define ROOM_MIN_X             4
#define ROOM_MIN_Y             2
#define ROOM_MAX_X             14
#define ROOM_MAX_Y             8




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
