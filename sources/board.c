#include "../headers/board.h"
#include "../headers/history.h"
#include <stdio.h>
#include "stdlib.h"

void create_empty_board(Board* pboard){
  pboard->points = (Ppoint**)malloc(pboard->height*sizeof(Ppoint*));
  int i;
  for (i=0;i<pboard->height;i++){
    pboard->points[i] = (Ppoint*)malloc(pboard->width*sizeof(Ppoint));
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

bool add_point(Board* pboard, Coord coord){
  int i=coord.x;
  int j=coord.y;
  if (is_move_valid(pboard,coord)){
    pboard->points[i][j] = (Ppoint)malloc(sizeof(int));
    *(pboard->points[i][j])=1;
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

Coord* get_valid_moves(Board* pboard)
{
  int i;
  int j;
  Coord* valid_moves = NULL;
  Coord coord_temp;
  for(i=0 ; i < pboard->width ; i++){
    for(j=0 ; j < pboard->height ; j++){
        coord_temp.x = i;
        coord_temp.y = j;
        if(is_move_valid(pboard,coord_temp))
          printf("TO DO");
          // Add into valid_moves(valid_moves);
    }
  }
  return valid_moves;
}

bool is_move_valid(Board* pboard,Coord coord)
{
  /* TO DO */
  return NULL;
}

Board* initialize_rand(void)
{
  /* TO DO */
  return NULL;
}

void execute_action(Board* pboard, enum action action, Coord coord)
{
  /* TO DO */
}

bool is_game_over(Board* pboard)
{
  if(!get_valid_moves(pboard))
    return true;
  return false;
}
