#ifndef INC_1_08_OBJECTS_H
#define INC_1_08_OBJECTS_H

#include <stdint.h>
#include <vector>
#include <string.h>
#include "dims.h"
#include "character.h"
#include "dice.h"
#include "descriptions.h"
#include "dungeon.h"
#include "object.h"
#include "utils.h"
#include "npc.h"


class object
{
public:
  std::string name;
  std::string description;
  object_type_t type;
  uint32_t color;
  int32_t hit;
  dice damage;
  int32_t dodge;
  int32_t defence;
  int32_t weight;
  int32_t speed;
  int32_t attribute;
  int32_t value;
  uint32_t rarity;
  bool artifact;
  pair_t position;
  //This is the symbol that will be printed
  char symbol;
};

void generate_objects(dungeon *d, uint16_t num_objects);


#endif 
