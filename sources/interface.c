#include "../headers/history.h"
#include "../headers/interface.h"
#include <stdio.h>

/*@requires pboard not null
  @assigns nothing
  @ensures prints board, shows possible moves if hint set to true */
void print_board(Board* pboard, bool hint)
{
    int width = pboard->width;
    int height = pboard->height;
    int index[4] = {-1,-1,-1,-1};
    int i, j;
    /* rewriting print_board to resolve display bug */
    /* WORK IN PROGRESS */
/*    *//* print header (y coordinates) *//*
    printf("  ");
    for(i = 0 ; i < width ; i++) {
        *//* Header not displayed correctly if size > 99
         * Accepted because a board should not be as big.
         * A game on a board this big would be way too
         * long anyway.
         *//*
        if(i < 10)
            printf(" %d ", i);
        else {
            printf(" %d", i);
        }
    }
    printf("\n");
    *//* print x coordinates and board *//*
    for(i = 0 ; i < height ; i++) {
        *//* print x coordinates *//*
        if(i < 10)
            printf("%d ", i);
        else
            printf("%d", i);

        for(j = 0 ; j < width ; j++) {

            *//* print board line *//*
            printf("[");
            printf("%c", get_board_char(pboard, i, j));
            printf("]");
        }
        printf("\n");
    }

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");*/
    for(i = -1 ; i < height ; i++) {
        for(j = -1 ; j < width ; j++) {
            if (i==-1 && j==-1) {
            printf("   ");
            } else if (i==-1) {
	            if (j<10){
	                printf(" %d ",j);
	            } else if (j<100) {
	                printf(" %d",j);
	            } else {
	                printf("%d",j);
	            }
	        } else if (j==-1) {
	            if (i<10) {
                    printf(" %d ",i);
	            } else if (i<100) {
	                printf(" %d",i);
	            } else {
	                printf("%d",i);
	            }
	        } else {
	            if(pboard->points[i][j]) {
	                if (Move_search(get_lines_history(),j,i,index)) {
	                    printf("[0]");
	                } else {
	                    printf("[X]");
	                }
	            } else {
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

/*@requires pmove not null
  @assings pmove
  @ensures asks player to chose amongst possible lines and frees all those not chosen*/
void select_line(Move* pmove){
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
  *pmove=current;
}

char get_board_char(Board *pboard, int x, int y)
{
    char data = ' ';
    if(pboard->points[x][y])
        data = '0';
    if(pboard->points[x][y])
    return data;
}