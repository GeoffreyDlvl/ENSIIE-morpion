#include "../headers/board.h"
#include "../headers/history.h"
#include "../headers/interface.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <linux/limits.h>
#include <string.h>

bool check_file_test(FILE *fp){
 // TODO
}

bool read_file_test(Board* pboard, char* path){
// TODO
}

bool get_file_board_width_test(FILE *fp){
// TODO
}

bool get_file_board_height_test(FILE *fp){
// TODO
}

bool create_empty_board_test(int width,int height){
// TODO
}

bool get_valid_moves(Board* pboard){
// TODO
}

bool is_move_valid(Board* pboard,Coord coord,Move* pmove){
// TODO
}

bool is_move_in_board(Board* pboard,Coord coord){
// TODO
}

bool is_move_exists_already(Board* pboard,Coord coord){
// TODO
}

bool horizontal_search(Move* pcand_lines,Coord coord,Board* pboard){
// TODO
}

bool vertical_search(Move* pcand_lines,Coord coord,Board* pboard){
// TODO
}

bool NE_diagonal_search(Move* pcand_lines,Coord coord,Board* pboard){
// TODO
}

bool NW_diagonal_search(Move* pcand_lines,Coord coord,Board* pboard){
// TODO
}

bool initialize_rand(){
// TODO
}

bool add_point(Board* pboard, Coord coord){
// TODO
}

bool (Board* pboard, enum action action, bool* quit){
// TODO
}

bool is_game_over(Board* pboard){
// TODO
}

bool free_board(Board* pboard){
// TODO
}

bool get_random_number(int min, int max){
// TODO
}

bool remove_point(Board* pboard,Coord coord){
// TODO
}

bool remove_points(Board* pboard){
// TODO
}

bool save_board(Board* pboard){
// TODO
}
