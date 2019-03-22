#include "../headers/history.h"
#include "../headers/interface.h"

void print_board(Board* pboard, bool hint)
{
	int m = pboard->width;
	int n = pboard->height;
	int i,j;
	if (!hint) {
	for(i=0;i<n;i+=1) {
		printf("    ");
		for(j=0;j<m;j+1) {
			printf(" %d ");
		}
		printf("%t",i);
		for(j=0;j<m;j+=1) {
			printf("[");
			if(pboard->points[i][j] == 1) {
				printf("X");
			} else {
				printf(" ");
			}
			printf("]");
		}
		printf("\n");
	}
	} else {
		list_available_moves(pboard);
	}
	
}

void select_move(Board* pboard,Coord coord)
{
	int i,j;
	Ppoint p_point;
	int m = pboard->width;
	int n = pboard->height;
	printf("Select next point coordinates [x,y] :\n");
	scanf("%d%d",&i,&j);
	if(i >= 0 && j >= 0 && i < n && j < m) {
		if(is_move_valid(pboard, coord)) {
		
		/* TO DO: Add new move */
		}	
	}
}

enum action select_action(Board* pboard, Coord* coord, bool* hint)
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
			if(coord != NULL) { /* If no move already done */
				return CANCEL_MOVE;
			}
		break;
		case 'r': /* TO DO: If previous move deleted */
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

void list_available_moves(Board* pboard)
{
	/* TO DO */
	/*Coord coord = get_valid_moves(pboard);*/
}

void ask_help(Board* pboard)
{
  /* TO DO */
}

void print_help(void)
{
  /* TO DO */
}
