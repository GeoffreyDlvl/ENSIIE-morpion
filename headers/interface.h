#ifndef INTERFACE_H
#define INTERFACE_H

#include<plateau.h>

void print_board(int hint,Board board*);

int select_move(Board board*);

void list_available_moves(Board board*);

void ask_help(Board board*);

void print_help();




#endif
