#include "../headers/history.h"
#include "../headers/board.h"
#include "../headers/interface.h"

#include "stdlib.h"
#include <stdbool.h>

Move Move_create(){
  return NULL;
}

bool Move_isEmpty(Move move){
  return (move==NULL);
}

void Move_addM(Move* pMove,int x,int y){
  Move newmove=(Move)malloc(sizeof(Coord));
  newmove->previous=*pMove;
  newmove->next=NULL;
  newmove->x=x;
  newmove->y=y;
  if (!Move_isEmpty(*pMove)){
    (*pMove)->next=newmove;
  }
  *pMove=newmove;
}

void Move_popM(Move* pMove){
  Move tmp=*pMove;
  *pMove=(*pMove)->previous;
  (*pMove)->next=NULL;
  free(tmp);
  tmp=NULL;
}

int pMove_length(Move* pMove){
  Move current=*pMove;
  int counter=0;
  while (!Move_isEmpty(current)){
    current=current->previous;
    counter+=1;
  }
  return counter;
}

void pMove_free(Move* pMove){
  while (!Move_isEmpty(*pMove)){
    Move_popM(pMove);
  }
}

void Move_search(Move move,int x, int y,int index[]){
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
}

static HistoryList history;
void initialize_HistoryList(){
  history.moves=0;
  *(history.PfirstMove)=Move_create();
  *(history.PlastPlayedMove)=*(history.PfirstMove);
  *(history.PlastSavedMove)=*(history.PfirstMove);
}

static LinesList lines;
void initialize_LinesList(){
  lines.n_lines=0;
  lines.lines_history=NULL;
}

bool play_move(Board* pboard,Coord coord)
{
  if (!add_point(pboard,coord)){
    return false;
  }
  Move_addM(history.PlastPlayedMove,coord.x,coord.y);
  if (history.moves==1){
    history.PfirstMove=history.PlastPlayedMove;
  }
  *(history.PlastSavedMove)=*(history.PlastPlayedMove);
  return true;
}

void cancel_move(Board* pboard)
{
  Move cancelled_move=*(history.PlastPlayedMove);
  remove_point(pboard,*cancelled_move);
  *(history.PlastPlayedMove)=cancelled_move->previous;
  if (*(history.PlastSavedMove) != cancelled_move->next){
    Move_popM(history.PlastSavedMove);
  }
}

void replay_move(Board* pboard)
{
  Move cancelled_move=*(history.PlastSavedMove);
  play_move(pboard,*cancelled_move);
}

void free_history(void)
{
  pMove_free(history.PlastSavedMove);
}

void add_line(Move* pmove){
  if (pMove_length(pmove)!=5){
    pmove=select_line(pmove);
  }
  Move_addM(lines.lines_history,(*pmove)->x,(*pmove)->y);
  lines.n_lines+=1;
}
  
void remove_line(Move move){
  int x=move->x;
  int y=move->y;
  int index[4]={-1,-1,-1,-1};
  Move_search(move,x,y,index);
  int i;
  for (i=0;i<4;i++){
    if (index[i]!=-1){
      index[i]=(int)index[i]/5;
    }
  }
  /* à terminer */
}
