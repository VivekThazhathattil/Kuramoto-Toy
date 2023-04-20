#ifndef _CELL_H
#define _CELL_H

#include <math.h>
#include <stdlib.h>

#include "utils.h"

#define CONST_KIJ 1
#define KIJ_REFINE 10

typedef struct CELL_S{
  int id;
  position_t pos;
  position_t scr_pos;
  double* kij;
  double ang;
  double ang_vel;
} cell_t;

cell_t* initialize_cell(int, position_t, position_t, double*, int, int);
void destroy_cell(cell_t*);
void update_cell_ang(cell_t*, cell_t**, double, int);

#endif
