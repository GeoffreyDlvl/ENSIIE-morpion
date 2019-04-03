#include "../headers/board.h"
#include "../headers/history.h"
#include "../headers/interface.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

static char knownChars[4] = {'X','O','[',']'}; /* the known chars according to display */

Board create_empty_board(int width,int height){
  Board board;
  board.width=width;
  board.height=height;
  board.points = (Ppoint**)malloc(board.height*sizeof(Ppoint*));
  int i;
  for (i=0;i<board.height;i++){
    board.points[i] = (Ppoint*)malloc(board.width*sizeof(Ppoint));
  }
  i=0;
  int j;
  for (i=0;i<board.height;i++){
    for (j=0;j<board.width;j++){
      board.points[i][j]=NULL;
    }
  }
  return board;
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
  Move move=Move_create();
  if (is_move_valid(pboard,coord,&move)){
    pboard->points[i][j] = (Ppoint)malloc(sizeof(int));
    *(pboard->points[i][j])=1;
    add_line(&move);
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
  for (i=0;i<pboard->height;i++){
    for (j=0;j<pboard->width;j++){
      if (pboard->points[i][j]){
	free(pboard->points[i][j]);
	pboard->points[i][j]=NULL;
      }
    }
  }
}

bool checkIfCharExist(char c){
  int i;
  for(i=0 ; i < (int)sizeof(knownChars) ; i++){
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
/*
bool read_file(Board* pboard, char* path)
{
   TO DO 
  return NULL;
}
*/
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

bool is_move_valid(Board* pboard,Coord coord,Move* pMove){
  if (!is_move_in_board(pboard,coord)){
    return false;
  }
  if (!is_move_exists_already(pboard,coord)){
    return false;
  }
  Move candidate_lines=Move_create();
  horizontal_search(candidate_lines,coord,pboard);
  printf("okh\n");
  vertical_search(candidate_lines,coord,pboard);
  printf("okv\n");
  NE_diagonal_search(candidate_lines,coord,pboard);
  printf("okne\n");
  NW_diagonal_search(candidate_lines,coord,pboard);
  printf("oknw\n");
  if (Move_isEmpty(candidate_lines)){
    printf("This movement is not possible\n");
  }
  Move_print(candidate_lines);
  *pMove=candidate_lines;
  return true;
}

bool is_move_in_board(Board* pboard,Coord coord){
  int x=coord.x;
  int y=coord.y;
  if (x >= 0 && y>= 0 && x <= pboard->width && y <= pboard->height){
    return true;
  }
  printf("Selected coordinates are invalid.\n");
  return false;
}

bool is_move_exists_already(Board* pboard,Coord coord){
  int x=coord.x;
  int y=coord.y;
  if (pboard->points[x][y]){
    printf("This point exists already.\n");
    return false;
  }
  return true;
}

void horizontal_search(Move cand_lines,Coord coord,Board* pboard){
  int i=coord.y;
  int test=coord.x;
  int j;
  int counter=1;
  for (j=test;j<test+5;j++){
    if (!(j<pboard->width && pboard->points[i][j])){
      break;
    }
    counter++;
  }
  if (counter == 5){
    printf("Move is possible!\n");
    j=test;
    for (j=test;j<test+5;j++){
      Move_addM(&cand_lines,i,j);
    }
    if (!candidate_line(&cand_lines,&coord)){
      j=0;
      for (j=0;j<5;j++){
	Move_popM(&cand_lines);
      }
    }
    counter=1;
  }
  j=test;
  int firstpoint;
  for (j=test;j>test-5;j--){
    if (!(j>=0 && pboard->points[i][j])){
      break;
    }
    counter++;
    firstpoint=j;
  }
  if (counter == 5){
    printf("Move is possible!\n");
    j=firstpoint;
    for (j=firstpoint;j<firstpoint+5;j++){
      Move_addM(&cand_lines,i,j);
    }
    if (!candidate_line(&cand_lines,&coord)){
      j=0;
      for (j=0;j<5;j++){
	Move_popM(&cand_lines);
      }
    }
  }
}

void vertical_search(Move cand_lines,Coord coord,Board* pboard){
  int j=coord.x;
  int test=coord.y;
  int i;
  int counter=1;
  for (i=test;i<test+5;i++){
    if (!(i<pboard->height && pboard->points[i][j])){
      break;
    }
    counter++;
  }
  if (counter == 5){
    i=test;
    for (i=test;i<test+5;i++){
      Move_addM(&cand_lines,i,j);
    }
    if (!candidate_line(&cand_lines,&coord)){
      i=0;
      for (i=0;i<5;i++){
	Move_popM(&cand_lines);
      }
    }
    counter=1;
  }
  i=test;
  int firstpoint;
  for (i=test;i>test-5;i--){
    if (!(i>=0 && pboard->points[i][j])){
      break;
    }
    counter++;
    firstpoint=i;
  }
  if (counter == 5){
    i=firstpoint;
    for (i=firstpoint;i<firstpoint+5;i++){
      Move_addM(&cand_lines,i,j);
    }
    if (!candidate_line(&cand_lines,&coord)){
      i=0;
      for (i=0;i<5;i++){
	Move_popM(&cand_lines);
      }
    }
  }
}

void NE_diagonal_search(Move cand_lines,Coord coord,Board* pboard){
  int testx=coord.x;
  int testy=coord.y;
  int i;
  int counter=1;
  for (i=0;i<5;i++){
    if (!(testx+i<pboard->width && testy-i>=0 && pboard->points[testy-i][testx+i])){
      break;
    }
    counter++;
  }
  if (counter == 5){
    i=0;
    for (i=0;i<5;i++){
      Move_addM(&cand_lines,testy-i,testx+i);
    }
    if (!candidate_line(&cand_lines,&coord)){
      i=0;
      for (i=0;i<5;i++){
	Move_popM(&cand_lines);
      }
    }
    counter=1;
  }
  i=0;
  int firstpoint;
  for (i=0;i<5;i++){
    if (!(testy+i<pboard->height && testx-i>=0 && pboard->points[testy+i][testx-i])){
      break;
    }
    counter++;
    firstpoint=i;
  }
  if (counter == 5){
    i=firstpoint;
    for (i=firstpoint;i>firstpoint-5;i--){
      Move_addM(&cand_lines,testy-i,testx+i);
    }
    if (!candidate_line(&cand_lines,&coord)){
      i=0;
      for (i=0;i<5;i++){
	Move_popM(&cand_lines);
      }
    }
  }
}

void NW_diagonal_search(Move cand_lines,Coord coord,Board* pboard){
  int testx=coord.x;
  int testy=coord.y;
  int i;
  int counter=1;
  for (i=0;i<5;i++){
    if (!(testx-i>=0 && testy-i>=0 && pboard->points[testy-i][testx-i])){
      break;
    }
    counter++;
  }
  if (counter == 5){
    i=0;
    for (i=0;i<5;i++){
      Move_addM(&cand_lines,testy-i,testx-i);
    }
    if (!candidate_line(&cand_lines,&coord)){
      i=0;
      for (i=0;i<5;i++){
	Move_popM(&cand_lines);
      }
    }
    counter=1;
  }
  i=0;
  int firstpoint;
  for (i=0;i<5;i++){
    if (!(testy+i<pboard->height && testx+i<pboard->width && pboard->points[testy+i][testx+i])){
      break;
    }
    counter++;
    firstpoint=i;
  }
  if (counter == 5){
    i=firstpoint;
    for (i=firstpoint;i>firstpoint-5;i--){
      Move_addM(&cand_lines,testy-i,testx-i);
    }
    if (!candidate_line(&cand_lines,&coord)){
      i=0;
      for (i=0;i<5;i++){
	Move_popM(&cand_lines);
      }
    }
  }
}

Board initialize_rand(void)
{
  int width = get_random_number(10, 15);
  int height = get_random_number(10, 15);
  Board board=create_empty_board(width,height);
  int i, j;
  int random;
  for (i = 0 ; i < height ; i++)
  {
    for (j = 0 ; j < width ; j++)
    {
      random = get_random_number(0, 100);
      /* 50% chance to add a point */
      if (random < 50)
      {
        int* point = malloc(sizeof(int));
        *point = 1;
        board.points[i][j] = point;
      }
    }
  }
  return board;
}

void execute_action(Board* pboard, enum action action)
{
  if (action == PLAY_MOVE){
    Coord coord=select_move();
    play_move(pboard,coord);
  }
  else if (action == CANCEL_MOVE){
    cancel_move(pboard);
  }
  else if (action == REPLAY_MOVE){
    replay_move(pboard);
  }
  else{
    printf("On essaie déjà de faire compiler puis on verra après\n");
  }
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
