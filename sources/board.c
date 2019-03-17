#include "../headers/board.h"
#include <stdbool.h>
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
