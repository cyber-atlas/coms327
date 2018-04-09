#include "object.h"
#include <stdlib.h>
#include <cstring>
#include "dungeon.h"

void generate_objects(dungeon *d, uint16_t num_objects)
{
  object *obj;
  uint64_t selected_desc;
  uint32_t room;
  pair_t position;


  for(int i = 0; i < num_objects; ++i){
    obj = new object;

    //randomly select description
    selected_desc = rand_range(0, (d->object_descriptions).size()-1);
    memset(obj, 0, sizeof(*obj));

    do {
      room = rand_range(1, d->num_rooms - 1);
      position[dim_y] = rand_range(d->rooms[room].position[dim_y],
                                   d->rooms[room].position[dim_y] +
                                       d->rooms[room].size[dim_y] - 1);

      position[dim_x] = rand_range(d->rooms[room].position[dim_x],
                                   d->rooms[room].position[dim_x] +
                                       d->rooms[room].size[dim_x] - 1);

    }while(d->object_map[position[dim_y]][position[dim_x]]);

    obj->position[dim_y] = position[dim_y];
    obj->position[dim_x] = position[dim_x];
    obj->name = d->object_descriptions[selected_desc].get_name();
    obj->description = d->object_descriptions[selected_desc].get_description();
    obj->attribute = d->object_descriptions[selected_desc].get_attribute().roll();
    obj->color = d->object_descriptions[selected_desc].get_color();
    obj->damage = d->object_descriptions[selected_desc].get_damage();
    obj->defence = d->object_descriptions[selected_desc].get_defence().roll();
    obj->dodge = d->object_descriptions[selected_desc].get_dodge().roll();
    obj->hit = d->object_descriptions[selected_desc].get_hit().roll();
    obj->type = d->object_descriptions[selected_desc].get_type();
    obj->speed = d->object_descriptions[selected_desc].get_speed().roll();
    obj->value = d->object_descriptions[selected_desc].get_value().roll();
    obj->rarity = d->object_descriptions[selected_desc].get_rarity();
    obj->artifact = d->object_descriptions[selected_desc].get_artifact();

   //TODO where should I put the the symbol?::

   switch(obj->type)
  {
    case objtype_WEAPON:
      obj->symbol = '|';
      break;
    case objtype_OFFHAND:
      obj->symbol = ')';
      break;
    case objtype_RANGED:
      obj->symbol = '}';
      break;
    case objtype_LIGHT:
      obj->symbol = '[';
      break;
    case objtype_ARMOR:
      obj->symbol = ']';
      break;
    case objtype_HELMET:
      obj->symbol = '(';
      break;
      case objtype_FLASK:
        obj->symbol = '!';
      break;
      case objtype_GOLD:
        obj->symbol = '$';
      break;
      case objtype_AMMUNITION:
        obj->symbol = '/';
      break;
      case objtype_FOOD:
        obj->symbol = ',';
      break;
      case objtype_WAND:
        obj->symbol = '-';
      break;
      case objtype_CONTAINER:
        obj->symbol = '%';
      break;
      /*case objtype_STACK:
        obj->symbol = '&';
        break;     */ 
    case objtype_CLOAK:
      obj->symbol = '{';
    break;
    case objtype_GLOVES:
      obj->symbol = '\\';
    break;
    case objtype_BOOTS:
      obj->symbol = '=';
    break;
    case objtype_AMULET:
      obj->symbol = '"';
    break;
    case objtype_RING:
      obj->symbol = '_';
    break;
    case objtype_SCROLL:
      obj->symbol = '~';
    break;
    case objtype_BOOK:
      obj->symbol = '?';
    break;

    default:
    //Tis is used for debuging
      obj->symbol = '*';
      break;
}

    d->object_map[position[dim_y]][position[dim_x]] = obj;
  }
}
