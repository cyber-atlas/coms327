#ifndef DIMS_H
# define DIMS_H

/* You can't forward reference enums or array types, so most of the headers *
 * need this, thus we put it in it's own file.                              */

typedef enum dim {
  dim_x,
  dim_y,
  num_dims
} dim_t;

//enumerated the equipment to make it easier to deal with
typedef enum equipment {
  weapon,
  offhand,
  ranged,
  armor,
  helmet,
  cloak,
  gloves,
  boots,
  amulet,
  light,
  ring_one,
  ring_two
} equipment_t;

typedef int16_t pair_t[num_dims];

#endif
