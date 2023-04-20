#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>


#include "utils.h"
#include "cell.h"

#define NUM_COLORS 7

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

#define reset "\e[0m"
#define CRESET "\e[0m"
#define COLOR_RESET "\e[0m"

#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

/* Checking if a toy model of Kuramoto works or not */
/* Idea: Each cell cycles through the 7 colors depending on their angle.
 * According to Kuramoto model, we'd expect to see all the cells pulsate
 * with same color at some point of time. Let's see if actually works or not :)
 */

typedef struct WINSIZE_S{
    int rows, cols;
} winsize_t;

winsize_t get_win_size(void){
  winsize_t ws;
  struct winsize win;     
  ioctl(0, TIOCGWINSZ, &win);
  ws.rows = win.ws_row;
  ws.cols = win.ws_col;
  return ws;
}

char* get_color(int num){
  char* colors[NUM_COLORS] = {RED, GRN, YEL, BLU, MAG, CYN, WHT};
  return colors[num%7];
}

void draw_cells(char* c, position_t pos, int color_id){
  gotoxy(pos.x, pos.y);
  char* color = get_color(color_id);
  printf("%s%s", color, c);
}

int main(void){
  srand(time(0));
  /* Testing for a sample grid 6x3 */
  int num_cells_x = 10;
  int num_cells_y = 10;
  int num_cells = num_cells_x * num_cells_y;
  char* blk_sym = "■";
  double tstep = 0.001;
  double total_time = 1;
  int frame_update_delay = 1e4;

  winsize_t scr_dims = get_win_size();
  position_t scr_mid = {scr_dims.cols/2, scr_dims.rows/2};

  cell_t** cells = (cell_t**) malloc(sizeof(cell_t*) * num_cells);

  int id = 0;
  for(int i = -num_cells_x/2 ; i < num_cells_x - num_cells_x/2; ++i){
    for(int j = -num_cells_y/2; j < num_cells_y - num_cells_y/2; ++j){
      position_t pos = {scr_mid.x + i, scr_mid.y + j};
      cells[id] = initialize_cell(id, pos, num_cells, 1);
      ++id;
    }
  }

  for(double curr_time = 0; curr_time < total_time; curr_time += tstep){
    usleep(frame_update_delay);
    for(int i = 0; i < num_cells; ++i){
        //int color_id = rand()%7;
        int color_id = round(to_deg(cells[i]->ang)*7/360);
        draw_cells(blk_sym, cells[i]->scr_pos, color_id);
        update_cell_ang(cells[i], cells, tstep, num_cells);
    }
    printf("\n");
  }
  
  for(int i = 0; i < num_cells; ++i)
    destroy_cell(cells[i]);
  free(cells);

  return 0;
}
