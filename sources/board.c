#include "../headers/board.h"
#include "stdlib.h"

void create_empty_board(Board* pboard){
  pboard->points = (Pcoord**)malloc(pboard->height*sizeof(Pcoord*));
  int i;
  for (i=0;i<pboard->height;i++){
    pboard->points[i] = (Pcoord*)malloc(pboard->width*sizeof(Pcoord));
  }
  i=0;
  int j;
  for (i=0;i<pboard->height;i++){
    for (j=0;j<pboard->width;j++){
      pboard->points[i][j]=NULL;
    }
  }
}

void free_board(Board* pboard){
  int i;
  for (i=0;i<pboard->height;i++){
    free(pboard->points[i]);
    pboard->points[i]=NULL;
  }
  free(pboard->points);
  pboard->points=NULL;
}

bool add_point(Board* pboard, Pcoord pcoord){
  if (is_move_valid(pboard,pcoord)){
    int i=pcoord->x;
    int j=pcoord->y;
    pboard->points[i][j] = (Pcoord)malloc(sizeof(Coord));
    pboard->points[i][j]->x = i;
    pboard->points[i][j]->y = j;
    return true;
  }
  else{
    return false;
  }
}

bool check_file(char* path)
{
  /* TO DO */
  return NULL;
}

bool read_file(Board* pboard, char* path)
{
  /* TO DO */
  return NULL;
}

Pcoord* get_valid_moves(Board* pboard)
{
  /* TO DO */
  return NULL;
}

bool is_move_valid(Board* pboard,Pcoord pcoord)
{
  /* TO DO */
  return NULL;
}

Board* initialize_rand(void)
{
  /* TO DO */
  return NULL;
}

void execute_action(Board* pboard, enum action action, Pcoord pcoord)
{
  /* TO DO */
}

bool is_game_over(Board* pboard)
{
  /* TO DO */
  return NULL;
}
