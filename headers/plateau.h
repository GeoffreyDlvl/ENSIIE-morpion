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
int read_file(Board* pboard, char* path); 
void create_empty_board(Board* pboard); 
Pcoord* get_valid_moves(Board* pboard);
int is_move_valid(Board* pboard,Pcoord pcoord);
Board* initialize_rand();
int play_move(Board* pboard,Pcoord pcoord);
int is_game_over(Board* pboard);

#endif
