#include "../headers/history.h"
#include "../headers/interface.h"
#include <stdio.h>

void print_board(Board* pboard, bool hint)
{
  int m = pboard->width;
  int n = pboard->height;
  int index[4]={-1,-1,-1,-1};
  int i,j;
    for(i=-1;i<n;i+=1) {
      for(j=-1;j<m;j+=1) {
	if (i==-1 && j==-1){
	  printf("   ");
	}
	else if (i==-1){
	  if (j<10){
	    printf(" %d ",j);
	  }
	  else if (j<100){
	    printf(" %d",j);
	  }
	  else{
	    printf("%d",j);
	  }
	}
	else if (j==-1){
	  if (i<10){
	    printf(" %d ",i);
	  }
	  else if (i<100){
	    printf(" %d",i);
	  }
	  else{
	    printf("%d",i);
	  }
	}
        else{
	  if(pboard->points[i][j]) {
	    if (Move_search(get_lines_history(),i,j,index)){
	      printf("[0]");
	    }
	    else{
	      printf("[X]");
	    }
	  }
	  else{
	    printf("[ ]");
	  }
	}
      }
      printf("\n");
    }
    if (hint){
    /*list_available_moves(pboard);*/
    }
}

Coord select_move()
{
	int x,y;
	/* Ppoint p_point ;*/
	printf("Select next point coordinates [x,y] (press x then ENTER then press y then ENTER) :\n");
	scanf("%d%d",&x,&y);
	Coord coord;
	coord.x=x;
	coord.y=y;
	coord.previous=NULL;
	return coord;
}

enum action select_action()
{
	char c;
	while (1) {
	printf("Select : Play move [p] / Cancel previous move [c] / Replay cancelled move [r]\n         List valid moves [l] / Ask help [h]\n");
	scanf("%c",&c);
	switch(c) {
		case 'p':
			return PLAY_MOVE;
		break;
		case 'c':
		        return CANCEL_MOVE;

		break;
		case 'r': 
			return REPLAY_MOVE;
		break;
		case 'l':
			return LIST_MOVES;
		break;
		case 'h':
			return ASK_HELP;
		break;
	}
	}

  return -1;
}
/*
void list_available_moves(Board* pboard)
{
   TO DO 
	Coord coord = get_valid_moves(pboard);
}


	 
void ask_help(Board* pboard)
{
   TO DO 
}

void print_help(void)
{
   TO DO 
}
*/

Move select_line(Move* pmove){
  int choice;
  Move current=*pmove;
  int i=0;
  printf("List of possible moves :\n");
  printf("1 : ");
  while(!Move_isEmpty(current)){
    printf("[%d,%d]->",current->x,current->y);
    current=current->previous;
    i++;
    if (i%5==0){
      printf("[ ]\n");
      printf("%d : ",(i/5)+1);
    }
  }
  printf("Choose your line.\n");
  scanf("%d",&choice);
  i=0;
  current=*pmove;
  Move current2=*pmove;
  for (i=0;i<(choice-1)*5;i++){
    current=current->previous;
  }
  for (i=0;i<choice*5-1;i++){
    current2=current2->previous;
  }
  Move tmp=current2->previous;
  current2->previous=NULL;
  pMove_free(&tmp);
  printf("You have chosen:\n");
  Move_print(current);
  return current;
}
