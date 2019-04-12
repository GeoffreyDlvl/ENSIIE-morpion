#ifndef HISTORY_H
#define HISTORY_H

/**
 * \file history.h
 * \brief Records player moves during a game.
 * \authors Geoffrey DELVAL, Rémi GUIJARRO ESPINOSA, Gabriel MORAN, Clément PERESSE
 * \version lot_a
 * \date 03.2019
 *
 * Represents board.h upper layer. 
 * This class records player moves and allows to cancel or replay a move.
 *
 */

#include <stdbool.h> 
#include <stddef.h>
#include "board.h"


/**
 * \struct historyList
 * \brief Convenience structure for accessing played moves.
 *
 * Upper layer of the double linked-list that allows to 
 * decrease memory load by offering direct access to head
 * and tail of playedMoved double-linked list data structure. 
 *
 * It is intended to be used as a static variable inside history source.
 */
typedef struct{
	size_t moves; /**< Number of played moves since the beginning of the game */
	Move PfirstMove; /**< first move */ 
	Move PlastPlayedMove; /**< last played move */
	Move PlastSavedMove; /**< last saved move (e.g. move before a canceled move) */
}HistoryList;/* PlastPlayedMove and PlastPlayedMove are two seperate lists : allows cancelling and replaying consecutively multiple times */
/**< \brief historyList structure alias */

/**
 * \struct LinesList
 * \brief Convenience structure for accessing lines list.
 * 
 *
 * It is intended to be used as a static variable inside history source.
 */
typedef struct{
  size_t n_lines;
  Move lines_history; /* alignements (of length 5) are concatenated into one list*/
}LinesList;

/**
 * \fn bool play_move(Board* pboard, p_point p_point)
 * \brief Play a move, i.e. add a point on the Board.
 *
 * \param pboard Pointer to the Board being played.
 * \param p_point Pointer to selected coordinates.
 * \return true if point successfully added, false otherwise.
 */
bool play_move(Board* pboard, Coord coord);

/**
 * \fn void cancel_move(Board* pboard, p_point* pp_point)
 * \brief Withdraw a point from the Board.
 *
 * \param pboard Pointer to the Board being played.
 */
void cancel_move(Board* pboard);

/**
 * \fn void replay_move(Board* pboard, p_point* pp_point)
 * \brief Add a previously withdrawn point to the Board.
 *
 * \param pboard Pointer to the Board being played.
 * \param pp_point Pointer to pointer to replayed coordinates.
 */
void replay_move(Board* pboard);

/**
 * \fn void free_history();
 * \brief Free allocated memory of static history list
 */
void free_history(void);

/**
 * \fn function Move Move_create();
 * \brief creates empty Move
 *
 */
Move Move_create();

/**
 * \fn function Move Move_isEmpty();
 * \brief checks if move is empty
 *
 */
bool Move_isEmpty(Move move);

/**
 * \fn function Move Move_addM(Move* pMove,int x,int y);
 * \brief adds Move to pMove allocating memory on heap
 *
 */
void Move_addM(Move* pMove,int x,int y);

/**
 * \fn function Move Move_popM(Move* pMove);
 * \brief removes last move, pMove points to previous and
 * frees allocated memory
 */
void Move_popM(Move* pMove);

/**
 * \fn function pMove_length(Move* pMove);
 * \brief returns pMove length 
 */
int pMove_length(Move* pMove);

/**
 * \fn function pMove_free(Move* pMove);
 * \brief frees all allocated memory of pMove
 * 
 */
void pMove_free(Move* pMove);

/**
 * \fn function Move_print(Move move);
 * \brief prints move list
 * 
 */
void Move_print(Move move);
/**
 * \fn void pMove_search(Move move,int x,int y,int index[]);
 * \brief returns ordered index list of element position of length 4 
 * (a point can belong to maximum 4 lines) 
*/  
bool Move_search(Move move,int x, int y,int index[]);

/**
 * \fn void initialize_HistoryList();
 * \brief initializes HistoryList 
 */
void initialize_HistoryList();

/**
 * \fn Move get_lines_history();
 * \brief returns lines.lines_history
 * \ensures makes lines history accessible outside of history 
 */
Move get_lines_history();

/**
 * \fn Move get_points_history();
 * \brief returns history of points from PlastPlayedMove
 * \ensures makes points history accessible outside of history 
 */
Move get_points_history();

/**
 * \fn Move get_points_saved_history();
 * \brief returns history of points from PlastSavedMove
 * \ensures makes points history accessible outside of history 
 */
Move get_points_saved_history();

/**
 * \fn void initialize_LinesList();
 * \brief initializes LinesList 
 */
void initialize_LinesList();

/**
 * \fn function add_line(Move* pmove)
 * \brief adds line to LinesList
 */
void add_line(Move* pmove);


void line_numbers_of_Move(Move move,int index[]);

bool no_more_than_one_move_in_two_lines(Move* line1,Move* line2);

bool candidate_line(Move* cand_line);

/**
 * \fn void remove_line(Move move)
 * \param index={-1,-1,-1,-1}
 * \brief index contains line numbers containing move
 */
void remove_lines(Move move);

void initialize_HistoryList_from_string(char* s);

size_t get_move_count();

void translate_history_x_axis();

void translate_history_y_axis();

void board_expansion_history_translation(Coord coord);

#endif

