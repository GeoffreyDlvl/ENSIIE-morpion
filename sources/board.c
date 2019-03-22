#include "../headers/board.h"
#include "../headers/history.h"
#include "stdlib.h"

void create_empty_board(Board* pboard){
  /*TO DO*/
}

void free_board(Board* pboard){
  /*TO DO*/
}

bool add_point(Board* pboard, Ppoint p_point){
  /*TO DO*/
  return NULL;
}

bool check_file(char* path)
{
  /* TO DO */
  return NULL;
}

bool read_file(Board* pboard, char* path)
{
  /* TO DO */
  return NULL;
}

Coord* get_valid_moves(Board* pboard)
{
  /* TO DO */
  return NULL;
}

bool is_move_valid(Board* pboard,Coord coord)
{
  /* TO DO */
  return NULL;
}

Board* initialize_rand(void)
{
  /* TO DO */
  return NULL;
}

void execute_action(Board* pboard, enum action action, Coord coord)
{
  /* TO DO */
}

bool is_game_over(Board* pboard)
{
  if(!get_valid_moves(pboard))
    return true;
  return false;
}
