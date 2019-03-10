#ifndef INTERFACE_H
#define INTERFACE_H

/**
 * \file interface.h
 * \brief Manages the user/programm interaction
 * \authors Geoffrey DELVAL, Rémi GUIJARRO ESPINOSA, Gabriel MORAN, Clément PERESSE
 * \version lot_a
 * \date 03.2019 
 *
 * This class shows the current status of the game and asks for the users
 * instructions.
 */

#include "plateau.h"

/**
 * \fn print_board(int hint,Board* pboard)
 * \brief Function which prints the current status of the game, as well as a hint
 * \param hint : An integer
 * \param pboard : A board pointer, can't be NULL 
 * \return void
 */
void print_board(int hint,Board* pboard);

/**
 * \fn select_move(Board* pboard,int move_number)
 * \brief Function which allows the user to add another valid point
 * \param pboard : A board pointer, can't be NULL 
 * \return void
 */
void select_move(Board* pboard,int move_number);

/**
 * \fn list_available_moves(Board* pboard)
 * \brief Function which prints a list of all valid moves
 * \param pboard : A board pointer, can't be NULL 
 * \return void
 */
void list_available_moves(Board* pboard);

/**
 * \fn ask_help(Board* pboard)
 * \brief Function which asks the user if he needs help (i.e. after a few failed
 * moves).
 * \param pboard : A board pointer, can't be NULL 
 * \return void
 */
void ask_help(Board* pboard);

/**
 * \fn print_help()
 * \brief Function which prints some help for the user
 * \return void
 */
void print_help();

#endif
