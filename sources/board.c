#include "../headers/board.h"
#include "../headers/history.h"
#include "../headers/interface.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

static char knownChars[4] = {'X','O','[',']'}; /* the known chars according to display */

/*@requires width and height greater than 0
  @assigns board
  @ensures return empty board (all points set to NULL) */
Board create_empty_board(int width,int height){
  Board board;
  board.width=width;
  board.height=height;
  /*allocated memory for points*/
  board.points = (Ppoint**)malloc(board.height*sizeof(Ppoint*));
  int i;
  for (i=0;i<board.height;i++){
    board.points[i] = (Ppoint*)malloc(board.width*sizeof(Ppoint));
  }
  i=0;
  int j;
  for (i=0;i<board.height;i++){
    for (j=0;j<board.width;j++){
      board.points[i][j]=NULL; /*all points set to NULL */
    }
  }
  return board;
}

/*@requires pboard not NULL
  @assigns pboard
  @ensures frees allocated memory of board */
void free_board(Board* pboard){
  int i;
  for (i=0;i<pboard->height;i++){
    free(pboard->points[i]);
    pboard->points[i]=NULL;
  }
  free(pboard->points);
  pboard->points=NULL;
}

/*@requires pboard not null
  @assigns pboard
  @ensures calls is_move_valid, allocates memory for square, sets it to 1 and adds associated line*/
bool add_point(Board* pboard, Coord coord){
  int i=coord.y;
  int j=coord.x;
  Move move=Move_create(); /* <- becomes list of possible moves after is_move_valid is called */
  if (is_move_valid(pboard,coord,&move)){
    pboard->points[i][j] = (Ppoint)malloc(sizeof(int));
    *(pboard->points[i][j])=1;
    add_line(&move);/* adds line to line history, calls select_line if there is more than 1 possible line*/
    return true;
  }
  else{
    return false;
  }
}

/*@requires pboard not null,point of coord exists in board
  @assigns pboard->points[i][j]
  @ensures frees allocated memory of point of coordinates coord and removes associates line*/
void remove_point(Board* pboard,Coord coord){
  int i=coord.x;
  int j=coord.y;
  free(pboard->points[i][j]);
  pboard->points[i][j]=NULL;
  remove_lines(&coord); /* remove all lines containing coord in lines history */
}

/*@requires pboard not null
  @assigns pboard
  @ensures frees all points from board */
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
    return false;
  }else{
    while((currentChar = fgetc(fp)) != EOF){
      if(!checkIfCharExist(currentChar)){
        return false;
      }
    }
    fclose(fp);
  }
  return true;
}

/*
int get_file_board_width(FILE *fp){
    char* array = NULL;
    size_t longeur = 0;
    return sizeof(getline(&array,&longeur,fp));
}

int get_file_board_height(FILE *fp){
    int cpt = 0;
    char* array;
    size_t longeur = 0;
    while((getline(&array,&longeur,fp)) !=  EOF){
        cpt++;
    }
    return cpt;
}
bool read_file(Board* pboard, char* path)
{
    if(!check_file(path)){
        return false;
    }else {
        FILE *fp;
        char currentChar;
        fp = fopen(path, "r");
        *pboard = (create_empty_board(get_file_board_width(fp),get_file_board_height(fp)));
        char* chars;
        size_t longeur = 0;
        int line = 0;
        while((getline(&chars,&longeur,fp)) !=  EOF){
            for(int col = 0 ; col < sizeof(chars) ; col++){
                if(chars[col] == knownChars[1]){ // if chars[col] == O
                    pboard->points[col][line] = (int * ) malloc(sizeof(int));
                    *(pboard->points[col][line]) = 1;
                }
            }
            line++;
        }
        fclose(fp);
    }
  return true;
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

/*@requires pboard not null
  @assigns pMove
  @ensures tests if point is valid -> see subsequent functions for details on conditions */
bool is_move_valid(Board* pboard,Coord coord,Move* pMove){
  if (!is_move_in_board(pboard,coord)){
    return false;
  }
  if (!is_move_exists_already(pboard,coord)){
    return false;
  }
  Move candidate_lines=Move_create();
  horizontal_search(&candidate_lines,coord,pboard);
  vertical_search(&candidate_lines,coord,pboard);
  NE_diagonal_search(&candidate_lines,coord,pboard);
  NW_diagonal_search(&candidate_lines,coord,pboard);
  if (Move_isEmpty(candidate_lines)){
    printf("This movement is not possible\n");
    return false;
  }
  *pMove=candidate_lines; /*at this stage *pMove is the list of all possible lines */
  return true;
}

/*@requires pboard not null
  @assigns nothing
  @ensures returns true if point of coordinates coord is in board, else false*/
bool is_move_in_board(Board* pboard,Coord coord){
  int x=coord.x;
  int y=coord.y;
  if (x >= 0 && y>= 0 && x <= pboard->width && y <= pboard->height){
    return true;
  }
  printf("Selected coordinates are invalid.\n");
  return false;
}

/*@requires pboard not null
  @assigns nothing
  @ensures returns true if point of coordinates coord exists already, else false */
bool is_move_exists_already(Board* pboard,Coord coord){
  int x=coord.x;
  int y=coord.y;
  if (pboard->points[y][x]){
    printf("This point exists already.\n");
    return false;
  }
  return true;
}

/*@requires pboard,pcand_lines not null
  @assigns pcand_lines
  @ensures searches horizontally for hypothetical lines, calls candidate_line to test if they are possible, then adds them to pcand_lines*/
void horizontal_search(Move* pcand_lines,Coord coord,Board* pboard){
  Move cand_lines=*pcand_lines;
  int i=coord.y;
  int test=coord.x;
  int j;
  int counter=1;
  for (j=test+1;j<test+5;j++){
    if (!(j<pboard->width && pboard->points[i][j])){
      break;
    }
    counter++;
  }/*searching for points on the horizontal right*/
  j=test;
  int firstpoint=test; /* <- useful to determine number of lines possible */
  for (j=test-1;j>test-5;j--){
    if (!(j>=0 && pboard->points[i][j])){
      break;
    }
    counter++;
    firstpoint=j;
  }/*searching for points on the horizontal left*/
  if (counter >= 5){
    j=firstpoint;
    int k=firstpoint;
    for (firstpoint=k;firstpoint<=k+counter-5;firstpoint++){/* for each firstpoint (every possible line)*/
      for (j=firstpoint;j<firstpoint+5;j++){/* add line to cand_lines */
	Move_addM(&cand_lines,j,i); 
      }
      if (!candidate_line(&cand_lines)){ /*if candidate line has more than one point in common with another line remove it*/
	j=0;
	for (j=0;j<5;j++){
	  Move_popM(&cand_lines);
	}
      }
    }
  }
  *pcand_lines=cand_lines;/*updates list of possible lines*/
}

/*@requires pboard,pcand_lines not null
  @assigns pcand_lines
  @ensures searches vertically for hypothetical lines, calls candidate_line to test if they are possible, then adds them to pcand_lines*/
void vertical_search(Move* pcand_lines,Coord coord,Board* pboard){
  Move cand_lines=*pcand_lines;
  int j=coord.x;
  int test=coord.y;
  int i;
  int counter=1;
  for (i=test+1;i<test+5;i++){
    if (!(i<pboard->height && pboard->points[i][j])){
      break;
    }
    counter++;
  }/*searching for points on the downoard vertical */
  i=test;
  int firstpoint=test; /* <- useful to determine number of lines possible */
  for (i=test-1;i>test-5;i--){
    if (!(i>=0 && pboard->points[i][j])){
      break;
    }
    counter++;
    firstpoint=i;
  }/*searching for points on the upwoard vertical */
  if (counter >= 5){
    i=firstpoint;
    int k=firstpoint;
    for (firstpoint=k;firstpoint<=k+counter-5;firstpoint++){/* for each firstpoint (every possible line)*/
      for (i=firstpoint;i<firstpoint+5;i++){/* add line to cand_lines */
	Move_addM(&cand_lines,j,i);
      }
      if (!candidate_line(&cand_lines)){ /*if candidate line has more than one point in common with another line remove it*/
	i=0;
	for (i=0;i<5;i++){
	  Move_popM(&cand_lines);
	}
      }
    }
  }
  *pcand_lines=cand_lines;/*updates list of possible lines*/
}

/*@requires pboard,pcand_lines not null
  @assigns pcand_lines
  @ensures searches on the north east diagonal for hypothetical lines, calls candidate_line to test if they are possible, then adds them to pcand_lines*/
void NE_diagonal_search(Move* pcand_lines,Coord coord,Board* pboard){
  Move cand_lines=*pcand_lines;
  int testx=coord.x;
  int testy=coord.y;
  int i;
  int counter=1;
  for (i=1;i<5;i++){
    if (!(testx+i<pboard->width && testy-i>=0 && pboard->points[testy-i][testx+i])){
      break;
    }
    counter++;
  }/*searching for points on the north east diagonal */
  i=0;
  int firstpoint=0;/* <- useful to determine number of lines possible */
  for (i=1;i<5;i++){
    if (!(testy+i<pboard->height && testx-i>=0 && pboard->points[testy+i][testx-i])){
      break;
    }
    counter++;
    firstpoint=i;
  }/*searching for points on the south west diagonal */
  if (counter >= 5){
    i=firstpoint;
    int k=firstpoint;
    for (firstpoint=k;firstpoint>=k-(counter-5);firstpoint--){/* for each firstpoint (every possible line)*/
      for (i=firstpoint;i>firstpoint-5;i--){/* add line to cand_lines */
	Move_addM(&cand_lines,testx-i,testy+i);
      }
      if (!candidate_line(&cand_lines)){/*if candidate line has more than one point in common with another line remove it*/
	i=0;
	for (i=0;i<5;i++){
	  Move_popM(&cand_lines);
	}
      }
    }
  }
  *pcand_lines=cand_lines;/*updates list of possible lines*/
}

/*@requires pboard,pcand_lines not null
  @assigns pcand_lines
  @ensures searches on the north west diagonal for hypothetical lines, calls candidate_line to test if they are possible, then adds them to pcand_lines*/
void NW_diagonal_search(Move* pcand_lines,Coord coord,Board* pboard){
  Move cand_lines=*pcand_lines;
  int testx=coord.x;
  int testy=coord.y;
  int i;
  int counter=1;
  for (i=1;i<5;i++){
    if (!(testx-i>=0 && testy-i>=0 && pboard->points[testy-i][testx-i])){
      break;
    }
    counter++;
  }/*searching for points on the north west diagonal */
  i=0;
  int firstpoint=0;/* <- useful to determine number of lines possible */
  for (i=1;i<5;i++){
    if (!(testy+i<pboard->height && testx+i<pboard->width && pboard->points[testy+i][testx+i])){
      break;
    }
    counter++;
    firstpoint=i;
  }/*searching for points on the south east diagonal */
  if (counter >= 5){
    i=firstpoint;
    int k=firstpoint;
    for (firstpoint=k;firstpoint>=k-(counter-5);firstpoint--){/* for each firstpoint (every possible line)*/
      for (i=firstpoint;i>firstpoint-5;i--){/* add line to cand_lines */
	Move_addM(&cand_lines,testx+i,testy+i);
      }
      if (!candidate_line(&cand_lines)){/*if candidate line has more than one point in common with another line remove it*/
	i=0;
	for (i=0;i<5;i++){
	  Move_popM(&cand_lines);
	}
      }
    }
  }
  *pcand_lines=cand_lines;/*updates list of possible lines*/
}

/*@requires nothing
  @assigns board
  @ensures creates empty board and fills it with random distribution of points*/
Board initialize_rand(void)
{
/*  int width = get_random_number(10, 15);
  int height = get_random_number(10, 15);
  Board board=create_empty_board(width,height);
  int i, j;
  int random;
  for (i = 0 ; i < height ; i++)
  {
    for (j = 0 ; j < width ; j++)
    {
      random = get_random_number(0, 100);
      *//* 50% chance to add a point *//*
      if (random < 50)
      {
        Ppoint point = malloc(sizeof(enum point));
        *point = 1;
        board.points[i][j] = point;
      }
    }
  }
  *//*horizontal_lines_on_init(&board);*//*
  return board;*/

    Board board = create_empty_board(6,6);
    Ppoint p1 = malloc(sizeof(enum point));
    Ppoint p2 = malloc(sizeof(enum point));
    Ppoint p3 = malloc(sizeof(enum point));
    Ppoint p4 = malloc(sizeof(enum point));
    board.points[0][0] = p1;
    board.points[0][1] = p2;
    board.points[0][2] = p3;
    board.points[0][3] = p4;

    return board;
}

/*@requires pboard not null
  @assigns pboard
  @ensures executes action of the enum action action*/
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

/*@requires pboard not null
  @assigns nothing
  @ensures returns true if game is over(if no moves available), else false*/
bool is_game_over(Board* pboard)
{
  if(!get_valid_moves(pboard))   /* <- à discuter */
    return true;
  return false;
}

/*@requires nothing 
  @assigns nothing
  @ensures returns randon number between min and max */
int get_random_number(int min, int max)
{
  int random = rand() % (max - min + 1) + min;
  return random;
}

/* UNFINISHED + WILL NOT BE IMPLEMENTED RIGHT NOW
void horizontal_lines_on_init(Board* pboard)
{
    int i, j;
    int neighbors_count;
    bool lineFound;
    for(i=0 ; i<pboard->height ; i++) {
        neighbors_count = 0;
        lineFound = false;
        for(j=0 ; j<pboard->width ; j++) {
            if(pboard->points[i][j]) {
                neighbors_count++;
            } else {
                neighbors_count = 0;
            }
            if(neighbors_count == 5) {
                lineFound = true;
            }
            if(neighbors_count > )
        }
    }
}*/
