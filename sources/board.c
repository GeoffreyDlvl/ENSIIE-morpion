#include "../headers/board.h"
#include "../headers/history.h"


#include <stdlib.h>
#include <time.h>
#include <stdio.h>

static char knownChars[4] = {'X','O','[',']'}; /* the known chars according to display */

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
  Move* pmove=NULL;
  if (is_move_valid(pboard,coord,pmove)){
    pboard->points[i][j] = (Ppoint)malloc(sizeof(int));
    *(pboard->points[i][j])=1;
    add_line(pmove);
    return true;
  }
  else{
    return false;
  }
}

void remove_point(Board* pboard,Coord coord){
  int i=coord.x;
  int j=coord.y;
  free(pboard->points[i][j]);
  pboard->points[i][j]=NULL;
  remove_lines(&coord);
}

void remove_points(Board* pboard){
  int i;
  int j;
  for (i=0;pboard->height;i++){
    for (j=0;pboard->width;j++){
      if (pboard->points[i][j]){
	free(pboard->points[i][j]);
	pboard->points[i][j]=NULL;
      }
    }
  }
}

bool checkIfCharExist(char c){
  int i;
  for(i=0 ; i < sizeof(knownChars) ; i++){
    if(c == knownChars[i])
      return true;
  }
  return false;
}

bool check_file(char* path)
{
  FILE *fp;
  char currentChar;
  fp = fopen(path, "r");
  if(fp == NULL){
    return false; /* perhaps should return an error code instead of just a bool to know the error status ex :  -1 can't open file.. */
  }else{
    while((currentChar = fgetc(fp)) != EOF){
      if(!checkIfCharExist(currentChar)){
        return false; /* TO DO : Specify the file verification process in order to enrich it */
      }
    }
  }
  return true;
}

bool read_file(Board* pboard, char* path)
{
  /* TO DO */
  return NULL;
}

Move get_valid_moves(Board* pboard)
{
  int i;
  int j;
  Move* pmove=NULL;
  Move valid_moves = Move_create();
  Coord coord_temp;
  for(i=0 ; i < pboard->width ; i++){
    for(j=0 ; j < pboard->height ; j++){
        coord_temp.x = i;
        coord_temp.y = j;
        if(is_move_valid(pboard,coord_temp,pmove)){
          Move_addM(&valid_moves,i,j);
	      }
    }
  }
  return valid_moves;
}

bool is_move_valid(Board* pboard,Coord coord,Move* pMove)
{
  if (!is_move_in_board(pboard,coord)){
    return false;
  }
  if (!is_move_exists_already(pboard,coord)){
    return false;
  }
  return true;
}

bool is_move_in_board(Board* pboard,Coord coord){
  int x=coord.x;
  int y=coord.y;
  if (x >= 0 && y>= 0 && x <= pboard->width && y <= pboard->height){
    return true;
  }
  return false;
}

bool is_move_exists_already(Board* pboard,Coord coord){
  int x=coord.x;
  int y=coord.y;
  if (pboard->points[x][y]){
    return false;
  }
  return true;
}

Board* initialize_rand(void)
{
  int width = get_random_number(10, 15);
  int height = get_random_number(10, 15);
  Board* p_board = malloc(sizeof(Board));
  p_board->width = width;
  p_board->height = height;
  
  int i, j;
  int random;
  for (i = 0 ; i < height ; i++)
  {
    for (j = 0 ; j < width ; j++)
    {
      random = get_random_number(0, 100);
      /* 30% chance to add a point */
      if (random < 30)
      {
        int* point = malloc(sizeof(int));
        *point = 1;
        p_board->points[i][j] = point;
      }
    }
  }

  return p_board;
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

int get_random_number(int min, int max)
{
  int random = rand() % (max - min + 1) + min;
  return random;
}
