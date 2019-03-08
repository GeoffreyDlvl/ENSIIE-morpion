#ifndef PLATEAU_H
#define PLATEAU_H


typedef struct 
{
    int x;
    int y;
} Coord;

typedef struct Coord* Pcoord; 


typedef struct
{
    int width;
    int height;
    Pcoord** points;
} Board;

int check_file(char* path); 
int read_file(Board* board, char* path); 
void create_empty_board(Board* board); 
Pcoord* get_valid_moves(Board* board);
int is_move_valid(Board* board,Pcoord pcoord);
Board* initialize_rand(int width,int height);
int play_move(Board* board,Pcoord pcoord);
int is_game_over(Board* board);

#endif
