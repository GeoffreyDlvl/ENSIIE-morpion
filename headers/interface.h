#ifndef INTERFACE_H
#define INTERFACE_H

#include "plateau.h"

void print_board(int hint,Board* pboard);

void select_move(Board* pboard,int move_number);

void list_available_moves(Board* pboard);

void ask_help(Board* pboard);

void print_help();



#endif
