#include "../headers/board.h"
#include "../headers/history.h"
#include "../headers/interface.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <linux/limits.h>
#include <string.h>

static int points_scored;
static const char* saving_path = "boards/saves/";

void increment_points_scored(){
    points_scored++;
}

int get_points_scored(){
    return points_scored;
}

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
  int error=0;
  Move move=Move_create(); /* <- becomes list of possible moves after is_move_valid is called */
  if (is_move_valid(pboard,coord,&move,&error)){
    pboard->points[i][j] = (Ppoint)malloc(sizeof(int));
    *(pboard->points[i][j])=1;
    add_line(&move);/* adds line to line history, calls select_line if there is more than 1 possible line*/
    return true;
  }
  else{
    print_error(&error);
    return false;
  }
}

/*@requires pboard not null,point of coord exists in board
  @assigns pboard->points[i][j]
  @ensures frees allocated memory of point of coordinates coord and removes associates line*/
void remove_point(Board* pboard,Coord coord){
  int j=coord.x;
  int i=coord.y;
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

bool check_file(FILE *fp)
{
    if(fp == NULL) {
        printf("Error while opening the file.");
        return false;
    }

    char* lineBuffer = NULL;
    size_t bufferSize = 0; /* if set to 0, then getline() will allocate the buffer */
    size_t width = getline(&lineBuffer, &bufferSize, fp) - 1; /* Get the length line, ie the width (minus '\n') */
    free(lineBuffer);

    lineBuffer = NULL;
    bufferSize = 0;
    fseek(fp, 0, SEEK_SET); /* Set cursor at the beginning of the file */
    size_t col;
    while((getline(&lineBuffer, &bufferSize, fp)) !=  EOF) {
        /* Line history delimiter, exit while loop */
        if(strcmp(lineBuffer, "====\n") == 0)
            break;

        if(strlen(lineBuffer) - 1 != width) {
            fprintf(stderr, "File error: board width must be equal for each line.");
            return false;
        }

        for (col = 0; col < width ; col++) {
            /* check if char is valid */
            if (lineBuffer[col] != '.' && lineBuffer[col] != 'o' && lineBuffer[col] != '\n') {
                fprintf(stderr, "File error: unknown character.");
                return false;
            }
        }
    }
    return true;
}

size_t get_file_board_width(FILE *fp) {
    fseek(fp, 0, SEEK_SET);
    char* line = NULL;
    size_t lineLength = 0;
    size_t width;
    width = getline(&line,&lineLength,fp) - 1; /* Get the length line, ie the width (minus '\n') */
    free(line);
    return width;
}

size_t get_file_board_height(FILE *fp){
    fseek(fp,0, SEEK_SET);
    size_t height = 0;
    char* line = NULL;
    size_t lineLength = 0;
    while((getline(&line, &lineLength, fp)) !=  EOF){
        /* line history delimiter */
        if(strcmp(line, "====\n") == 0)
            break;

        height++;
    }
    free(line);
    return height;
}
bool read_file(Board* pboard, char* path)
{
    FILE *fp = fopen(path, "r");
    if(!check_file(fp)) {
        return false;
    }

    size_t width = get_file_board_width(fp);
    size_t height = get_file_board_height(fp);
    *pboard = create_empty_board(width, height);

    size_t line = 0, col = 0;
    char* lineBuffer;
    size_t bufferSize;
    fseek(fp, 0, SEEK_SET);
    while(getline(&lineBuffer, &bufferSize, fp) != EOF) {
        if(strcmp(lineBuffer, "====\n") == 0) {
            getline(&lineBuffer, &bufferSize, fp);
            initialize_HistoryList_from_string(lineBuffer);
            break;
        }
        for(col = 0 ; col < width ; col++) {
            if(lineBuffer[col] == 'o') {
                Ppoint point = malloc(sizeof(int));
                pboard->points[line][col] = point;
            }
        }
        line++;
    }
    points_scored = 0;
    free(lineBuffer);
    fclose(fp);
    return true;
}

void get_valid_moves(Board* pboard,Move* pvalid_points)
{
  int i;
  int j;
  int error=0;
  Move valid_points=*pvalid_points;
  Move valid_moves=Move_create();
  Coord coord_temp;
  for(i=0 ; i < pboard->height ; i++){
    for(j=0 ; j < pboard->width ; j++){
      coord_temp.x = j;
      coord_temp.y = i;
      if(is_move_valid(pboard,coord_temp,&valid_moves,&error)){
	pMove_free(&valid_moves);
	Move_addM(&valid_points,coord_temp.x,coord_temp.y);
      }
    }
  }
}

void print_error(int* error){
  int n_error=*error;
  if (n_error==1){
    printf("Selected coordinates are invalid.\n");
  }
  else if (n_error==2){
    printf("This point exists already.\n");
  }
  else if (n_error==3){
    printf("Impossible move : either no available alignement or all available alignements have more than one point in common with selected point.\n");
  }
}

/*@requires pboard not null
  @assigns pMove
  @ensures tests if point is valid -> see subsequent functions for details on conditions */
bool is_move_valid(Board* pboard,Coord coord,Move* pMove,int* error){
  if (!is_move_in_board(pboard,coord)){
    *error=1;
    return false;
  }
  if (is_move_exists_already(pboard,coord)){
    *error=2;
    return false;
  }
  Move candidate_lines=Move_create();
  horizontal_search(&candidate_lines,coord,pboard);
  vertical_search(&candidate_lines,coord,pboard);
  NE_diagonal_search(&candidate_lines,coord,pboard);
  NW_diagonal_search(&candidate_lines,coord,pboard);
  if (Move_isEmpty(candidate_lines)){
    *error=3;
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
  if (x >= 0 && y>= 0 && x < pboard->width && y < pboard->height){
    return true;
  }
  return false;
}

/*@requires pboard not null
  @assigns nothing
  @ensures returns true if point of coordinates coord exists already, else false */
bool is_move_exists_already(Board* pboard,Coord coord){
  int x=coord.x;
  int y=coord.y;
  if (pboard->points[y][x]){
    return true;
  }
  return false;
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
        Ppoint point = malloc(sizeof(int));
        board.points[i][j] = point;
      }
    }
  }
  /*horizontal_lines_on_init(&board);*/
  /*
    return board;*/
  /*
    Board board = create_empty_board(6,6);
    Ppoint p1 = malloc(sizeof(enum point));
    Ppoint p2 = malloc(sizeof(enum point));
    Ppoint p3 = malloc(sizeof(enum point));
    Ppoint p4 = malloc(sizeof(enum point));
    board.points[0][0] = p1;
    board.points[0][1] = p2;
    board.points[0][2] = p3;
    board.points[0][3] = p4;

    return board;*/
  return board;
}

/*@requires pboard not null
  @assigns pboard
  @ensures executes action of the enum action action*/
void execute_action(Board* pboard, enum action action, bool* quit)
{
    if (action == PLAY_MOVE){
        Coord coord=select_move();
        play_move(pboard,coord);
    } else if (action == CANCEL_MOVE){
        cancel_move(pboard);
    } else if (action == REPLAY_MOVE){
        replay_move(pboard);
    } else if (action == LIST_MOVES){
        list_available_moves(pboard);
    }else if (action == ASK_HELP){
        print_help();
        press_a_key_to_continue();
    } else if (action == QUIT_GAME){
        *quit = confirm_quit_save(pboard);
    } else{
        fprintf(stderr, "Execute action: action is undefined.");
    }
}

/*@requires pboard not null
  @assigns nothing
  @ensures returns true if game is over(if no moves available), else false
bool is_game_over(Board* pboard)
{
  if(!get_valid_moves(pboard))   
    return true;
    return false;
    }*/

/*@requires nothing 
  @assigns nothing
  @ensures returns randon number between min and max */
int get_random_number(int min, int max)
{
  int random = rand() % (max - min + 1) + min;
  return random;
}

void save_board(Board* pboard) {
    char resolved_path[PATH_MAX];
    char* fileName = ask_savefile_name();
    char path[PATH_MAX];
    strcpy(path,saving_path);
    strcat( path, fileName );
    free(fileName); /* No longer needed */
    realpath(path, resolved_path);
    FILE *fp = fopen(resolved_path, "w");
    int line, col;
    for(line = 0 ; line < pboard->height ; line++) {
        for(col = 0 ; col < pboard->width ; col++) {
            if (pboard->points[line][col]) {
                fputc('o', fp);
            } else {
                fputc('.', fp);
            }
        }
        fputc('\n', fp);
    }
    /* Save lines */
    fputs("====\n", fp);
    Move history = get_lines_history();
    int len = pMove_length(&history);
    Move currentMove = history;
    char buffer[16] = {0};
    if(len > 0) {
        sprintf(buffer, "%d,%d", currentMove->x, currentMove->y);
        fputs(buffer, fp);
        currentMove=currentMove->previous;
    }
    if(len > 1) {
        while (!Move_isEmpty(currentMove)){
            sprintf(buffer, "|%d,%d", currentMove->x, currentMove->y);
            fputs(buffer, fp);
            currentMove=currentMove->previous;
        }
    }
    fputc('\n', fp);

    fclose(fp);
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
