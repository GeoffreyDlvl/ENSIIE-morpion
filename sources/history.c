#include "../headers/history.h"
#include "../headers/board.h"
#include "../headers/interface.h"

#include "stdlib.h"
#include "stdio.h"
#include <stdbool.h>

/*@requires nothing
  @assigns nothing
  @ensures returns empty move*/
Move Move_create(){
  return NULL;
}

/*@requires nothing
  @assigns nothing
  @ensures returns true if move is empty else false*/
bool Move_isEmpty(Move move){
  return (move==NULL);
}

/*@requires pMove not null
  @assigns pMove
  @ensures adds(with allocation) struct Coord of coordinates x,y to Move list*/
void Move_addM(Move* pMove,int x,int y){
  Move newMove=(Move)malloc(sizeof(Coord));
  newMove->x=x;
  newMove->y=y;
  newMove->previous=*pMove;
  *pMove=newMove;
}

/*@requires pMove not null
  @assigns pMove
  @ensures removes and frees allocated last added struct Coord of Move list*/
void Move_popM(Move* pMove){
  Move tmp=*pMove;
  *pMove=(*pMove)->previous;
  free(tmp);
  tmp=NULL;
}

/* to test validity of lists, prints Move list */
void Move_print(Move move){
  Move currentMove=move;
  while (!Move_isEmpty(currentMove)){
    printf("[%d,%d]->",currentMove->x,currentMove->y);
    currentMove=currentMove->previous;
  }
  printf("[  ]\n");
}
/*returns Move list length*/
int pMove_length(Move* pMove){
  Move current=*pMove;
  int counter=0;
  while (!Move_isEmpty(current)){
    current=current->previous;
    counter+=1;
  }
  return counter;
}
/*frees allocated memory of Move list*/
void pMove_free(Move* pMove){
  Move move=*pMove;
  while (!Move_isEmpty(move)){
    Move_popM(&move);
  }
}
/*searches for Move of coordinates x,y in Move list and assigns index to positions*/
bool Move_search(Move move,int x, int y,int index[]){
  Move current=move;
  int i=0;
  int line=0;
  while (!Move_isEmpty(current)){
    if (current->x==x && current->y==y){
      index[line]=i;
      line++;
    }
    i++;
    current=current->previous;
  }
  if (line > 0){
    return true;
  }
  return false;
}

static HistoryList history;
void initialize_HistoryList(){
  history.moves=0;
  Move move=Move_create();
  history.PfirstMove=move;
  history.PlastPlayedMove=move;
  history.PlastSavedMove=move;
}

static LinesList lines;
void initialize_LinesList(){
  lines.n_lines=0;
  lines.lines_history=Move_create();
}

Move get_lines_history(){
  return lines.lines_history;
}

Move get_points_history(){
  return history.PlastPlayedMove;
}

bool play_move(Board* pboard,Coord coord){
  if (!add_point(pboard,coord)){
    return false;
  }
  if (history.moves >= 1 && history.PlastSavedMove->x!=history.PlastPlayedMove->x && history.PlastSavedMove->y!=history.PlastPlayedMove->y){
    Move_popM(&history.PlastSavedMove);/* <- removes last saved move if PlastPlayedMove and PlastSavedMove are not same moves*/
  }
  Move_addM(&history.PlastPlayedMove,coord.x,coord.y);
  history.moves+=1;
  if (history.moves==1){
    history.PfirstMove=&coord;
  }
  history.PlastSavedMove=&coord;
  return true;
}

void cancel_move(Board* pboard)
{
  Move cancelled_move=history.PlastPlayedMove;
  remove_point(pboard,*cancelled_move);
  history.PlastPlayedMove=cancelled_move->previous;
  if (history.moves >= 1 && history.PlastSavedMove->x != cancelled_move->x && history.PlastSavedMove->y != cancelled_move->y){
    Move_popM(&history.PlastSavedMove);
  }
}

void replay_move(Board* pboard)
{
  Move cancelled_move=history.PlastSavedMove;
  play_move(pboard,*cancelled_move);
}

void free_history(void)
{
  Move moveH=history.PlastSavedMove;
  Move moveL=lines.lines_history;
  Move_print(moveL);
  Move_print(moveH);
  /*pMove_free(&moveH);
    pMove_free(&moveL);*/
}

void add_line(Move* pmove){
  Move line=*pmove;
  if (pMove_length(&line)>5){
    select_line(&line);
  }
  while(!Move_isEmpty(line)){
    Move_addM(&lines.lines_history,line->x,line->y);
    Move_popM(&line);
  }
  lines.n_lines+=1;
}

bool no_more_than_one_move_in_two_lines(Move* line1,Move* line2){
  int i,j;
  int same_move=0;
  Move current1=*line1;
  Move current2=*line2;
  for (i=0;i<5;i++){
    current2=*line2;
    for (j=0;j<5;j++){
      if (current1->x == current2->x && current1->y == current2->y){
	same_move+=1;
	if (same_move > 1){
	  return false;
	}
      }
      current2=current2->previous;
    }
    current1=current1->previous;
  }
  return true;
}

void line_numbers_of_Move(Move move,int index[]){
  int x=move->x;
  int y=move->y;
  int i;
  Move_search(move,x,y,index);
  for (i=0;i<4;i++){
    if (index[i]!=-1){
      index[i]=(int)index[i]/5;
    }
  }
}

bool candidate_line(Move* cand_line){
  int i;
  Move current=lines.lines_history;
  while (!Move_isEmpty(current)){
    if(!no_more_than_one_move_in_two_lines(cand_line,&current)){
      printf("MORE_THAN_ONE_POINT_IN_COMMON\n");
      return false;
    }
    for (i=0;i<5;i++){
      current=current->previous;
    }
  }
  return true;
}


void remove_lines(Move move){
  int index[4]={-1,-1,-1,-1};
  line_numbers_of_Move(move,index);
  int i,j;
  int counter=0;
  Move current=lines.lines_history;
  Move next=current;
  for (i=0;i<4;i++){
    if (index[i]!=-1){
      while (!Move_isEmpty(current) && counter<5*(index[i]-i)){
	counter++;
	next=current;
	current=current->previous;
      }
      if (counter==0){
	for (j=0;j<5;j++){
	  Move_popM(&lines.lines_history);
	}
      }
      else{
	Move* Pcurrent=&current;
	for (j=0;j<5;j++){
	  Move_popM(Pcurrent);
	}
	next->previous=*Pcurrent;
      }
    }
  }
}
