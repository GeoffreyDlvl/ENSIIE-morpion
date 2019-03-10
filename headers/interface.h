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
 * \enum action
 * \brief Represents an game action.
 */
enum action 
{ 
	PLAY_MOVE, /**< Play a move */ 
	CANCEL_MOVE, /**< Cancel last move */
	REPLAY_MOVE, /**< Replay a canceled move */
	LIST_MOVES, /**< List all valid moves */
	ASK_HELP /**< Ask for help to be displayed */
};

/**
 * \fn print_board(Board* pboard, bool hint)
 * \brief Print the Board, as well as a hint (i.e. a list of available moves) if required.
 *
 * \param pboard Board pointer 
 * \param hint true if hint requested, false if hint NOT requested
 */
void print_board(Board* pboard, bool hint);

/**
 * \fn select_move(Board* pboard,int move_number)
 * \brief Ask the user to play a move.
 *
 * \param pboard Pointer to the Board
 * \param move_number Move number since game started
 */
void select_move(Board* pboard, int move_number);

/**
 * \fn enum choice select_action(Board* pboard, int move_number)
 * \brief Ask the user for the next action.
 *
 * \param pboard Pointer to the Board
 * \param move_number Move number since game started
 */
enum action select_action(Board* pboard, int move_number);

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
 * \fn print_help()
 * \brief Print help for the user
 */
void print_help();

#endif
