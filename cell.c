#include "cell.h"

#define RAND_NUM_PREC 1000

cell_t* initialize_cell(int id, position_t scr_pos, int num_cells, int const_kij){
  cell_t* cell = (cell_t*) malloc(sizeof(cell_t));
  cell->scr_pos = scr_pos;
  cell->kij = (double*) malloc(sizeof(double)*num_cells);
  for(int i = 0; i < num_cells; ++i){
    if(i == id){
      cell->kij[i] = 0.0;
    }
    else{
      if(const_kij)
        cell->kij[i] = CONST_KIJ;
      else{
        /* +1 for non-zero denominator */
        cell->kij[i] = 1/(rand()%KIJ_REFINE + 1);
      }
    }
  }
  double rand_num = (double)(rand()%RAND_NUM_PREC);
  cell->ang = 2*M_PI*rand_num/RAND_NUM_PREC;
  //printf("cell->ang = %f", cell->ang);
  rand_num = (double)(rand()%RAND_NUM_PREC);
  cell->ang_vel = 2*M_PI*rand_num/RAND_NUM_PREC;
  return cell;
}

void update_cell_ang(cell_t* cell, cell_t** other_cells,
    double tstep, int num_cells){

  double psi = 0;
  for(int i = 0; i < num_cells; ++i)
    psi += other_cells[i]->ang;
  psi = psi/num_cells;

  cell->ang = cell->ang + cell->ang_vel*tstep 
    - (CONST_KIJ*cos(psi - cell->ang)/num_cells);
}

void destroy_cell(cell_t* cell){
  /* remove state */ 
  free(cell->kij);
  free(cell);
}

double to_deg(double ang){
  return ang*180/M_PI;
}
