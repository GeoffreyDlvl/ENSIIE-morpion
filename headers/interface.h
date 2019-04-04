#ifndef INTERFACE_H
#define INTERFACE_H

/**
 * \file interface.h
 * \brief Displays the Board and manages the user/program interactions.
 * \authors Geoffrey DELVAL, Rémi GUIJARRO ESPINOSA, Gabriel MORAN, Clément PERESSE
 * \version lot_a
 * \date 03.2019 
 *
 * Handles displaying and asks the user for input.
 *
 */

#include <stdbool.h> 
#include "board.h"

/**
 * \fn print_board(Board* pboard, bool hint)
 * \brief Print the Board, as well as a hint (i.e. a list of available moves) if required.
 *
 * \param pboard Board pointer 
 * \param hint true if hint requested, false if hint NOT requested
 */
void print_board(Board* pboard, bool hint);

/**
 * \fn select_move(Board* pboard, Coord coord)
 * \brief Ask the user to play a move.
 *
 * \param pboard Pointer to the Board
 * \param coord Coordinates of the moves 
 */
Coord select_move();

/**
 * \fn enum action select_action(Board* pboard, p_point p_point, bool* hint)
 * \brief Ask the user for the next action.
 *
 * \param pboard Pointer to the Board
 * \param move_number Move number since game started
 * \param hint Hold the boolean signifying whether the user wishes to get a hint
 */
enum action select_action();

/**
 * \fn list_available_moves(Board* pboard)
 * \brief Prints a list of all valid moves.
 *
 * \param pboard Pointer to the Board 
 */
void list_available_moves(Board* pboard);

/**
 * \fn ask_help(Board* pboard)
 * \brief Ask the user for help (i.e. after a few failed
 * moves).
 *
 * \param pboard Pointer to the Board 
 * \return void
 */
void ask_help(Board* pboard);

/**
 * \fn print_help(void)
 * \brief Print help for the user
 */
void print_help(void);

/**
 * \fn select_line(Move* pmove)
 * \brief select among available lines (if more than 1 are available)
 */
void select_line(Move* pmove);

#endif
