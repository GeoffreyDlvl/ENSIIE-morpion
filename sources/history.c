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

/* @requires nothing
   @assigns nothing
   @ensures prints Move list */
void Move_print(Move move){
  Move currentMove=move;
  while (!Move_isEmpty(currentMove)){
    printf("[%d,%d]->",currentMove->x,currentMove->y);
    currentMove=currentMove->previous;
  }
  printf("[  ]\n");
}
/*@requires pMove not null
  @assigns nothing
  @ensures returns Move list length*/
int pMove_length(Move* pMove){
  Move current=*pMove;
  int counter=0;
  while (!Move_isEmpty(current)){
    current=current->previous;
    counter+=1;
  }
  return counter;
}
/*@requires pMove not null
  @assigns pMove
  @ensures frees allocated memory of Move list*/
void pMove_free(Move* pMove){
  Move move=*pMove;
  while (!Move_isEmpty(move)){
    Move_popM(&move); /*while move list isn't empty pop the first Move */
  }
}
/*@requires index of length 8 (this function is mainly used by lines_list and a point can belong to 8 lines maximum) 
  @assigns index
  @ensures searches for Move of coordinates x,y in Move list and assigns index to positions*/
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
  }/* at this stage, index contains positions of all the occurences of Coord(x,y) in Move list */
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
/*@requires nothing
  @assigns nothing
  @ensures makes lines history accessible outside of history.c */
Move get_lines_history(){
  return lines.lines_history;
}

/*@requires nothing
  @assigns nothing
  @ensures makes points history accessible outside of history.c */
Move get_points_history(){
  return history.PlastPlayedMove;
}

/*@requires pboard not null
  @assigns pboard
  @ensures plays desired move, returning true if successful, else false */
bool play_move(Board* pboard,Coord coord){
  if (!add_point(pboard,coord)){
    return false;
  }
  if (history.moves >= 1 && history.PlastSavedMove->x!=history.PlastPlayedMove->x && history.PlastSavedMove->y!=history.PlastPlayedMove->y){
    Move_popM(&history.PlastSavedMove);/* <- removes last saved move if PlastPlayedMove and PlastSavedMove are not same moves (player is cancelling more than once consecutively) */
  }
  Move_addM(&history.PlastPlayedMove,coord.x,coord.y);
  history.moves+=1;
  if (history.moves==1){ 
    history.PfirstMove=&coord; 
  }
  history.PlastSavedMove=&coord; /* once a move is played PlastSavedMove and PlastPlayedMove point to same Coord */
  return true;
}

/*@requires pboard not null
  @assigns pboard
  @ensures cancels last played move by calling remove point*/
void cancel_move(Board* pboard)
{
  Move cancelled_move=history.PlastPlayedMove;
  remove_point(pboard,*cancelled_move);
  history.PlastPlayedMove=cancelled_move->previous;
  if (history.moves >= 1 && history.PlastSavedMove->x != cancelled_move->x && history.PlastSavedMove->y != cancelled_move->y){
    Move_popM(&history.PlastSavedMove);
  }
}

/*@requires pboard not null
  @assigns pboard
  @ensures replays last saved move */
void replay_move(Board* pboard)
{
  Move cancelled_move=history.PlastSavedMove;
  play_move(pboard,*cancelled_move);
}

/*@requires nothing
  @assings lines and points histories
  @ensures frees allocated memory of lines and points histories */
void free_history(void)
{
  Move moveH=history.PlastSavedMove;
  Move moveL=lines.lines_history;
  Move_print(moveL);
  Move_print(moveH);
  /*pMove_free(&moveH);
    pMove_free(&moveL);*/
}

/*@requires pmove not null
  @assings pmove,lines history
  @ensures adds line to lines history, calls select line if more than 1 */
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

/*@requires line1 and line2 not null AND BOTH LISTS OF LENGTH AT LEAST 5
  @assigns nothing
  @ensures returns true if no more than one common move in both lines, else false*/
bool no_more_than_one_move_in_two_lines(Move* line1,Move* line2){
  int i,j;
  int same_move=0;
  Move current1=*line1;
  Move current2=*line2;
  for (i=0;i<5;i++){/*loop on first list */
    current2=*line2;
    for (j=0;j<5;j++){/*loop on second list */
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

/*@requires index of length 8 initialized with -1 values
  @assigns index
  @ensures index contains positions of lines containing move in lines history */
void line_numbers_of_Move(Move move,int index[]){ /* <- function mainly useful for remove_line */
  int x=move->x;
  int y=move->y;
  int i;
  Move_search(lines.lines_history,x,y,index);/*at this stage index contains positions of move in lines history */
  for (i=0;i<8;i++){
    if (index[i]!=-1){
      index[i]=(int)index[i]/5;
    }
  }/* at this stage index contains positions of lines containing move in lines history */
}

/*@requires cand_line not null and of length at least 5
  @assigns nothing
  @ensures returns true if candidate line has no more than one move in common with other lines, else false */
bool candidate_line(Move* cand_line){
  int i;
  Move current=lines.lines_history;
  while (!Move_isEmpty(current)){/*loop on lines history to compare with each line of lines history */
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

/*@requires nothing
  @assigns lines history
  @ensures removes all lines containing move from lines history */
void remove_lines(Move move){
  int index[4]={-1,-1,-1,-1,-1,-1,-1,-1};
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
