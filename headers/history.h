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
 * \struct playedMove
 * \brief Played moves since the beginning of the game.
 *
 * Data are saved in a double linked-list structure that contains all the played moves.
 */
struct playedMove
{
	Pcoord* coord; /**< Data: Pcoord pointer to this played move */
	struct playedMove* PpreviousPlayedMove; /**< Pointer to previous playedMove */
	struct playedMove* PnextPlayedMove; /**< Pointer to the next playedMove */
};


/**
 * \struct HistoryList
 * \brief Convenience structure for accessing played moves.
 *
 * Upper layer of the double linked-list that allows to 
 * decrease memory load by offering direct access to head
 * and tail of playedMoved double-linked list data structure. 
 */
typedef struct historyList
{
	size_t moves; /**< Number of played moves since the beginning of the game */
	struct playedMove* PfirstMove; /**< Pointer to the first move */ 
	struct playedMove* PlastPlayedMove; /**< Pointer to the last played move */
	struct playedMove* PlastSavedMove; /**< Pointer to the last saved move (e.g. move before a canceled move) */
} HistoryList;

/**
 * \fn bool play_move(Board* pboard, Pcoord pcoord)
 * \brief Add a point on the Board.
 *
 * \param pboard Pointer to the Board being played.
 * \param pcoord Pointer to selected coordinates.
 * \return true if point successfully added, false otherwise.
 */
bool play_move(Board* pboard, Pcoord pcoord,HistoryList* phistorylist);

/**
 * \fn void cancel_move(Board* pboard, Pcoord* ppcoord)
 * \brief Withdraw a point from the Board.
 *
 * \param pboard Pointer to the Board being played.
 * \param ppcoord Pointer to pointer to canceled coordinates.
 */
void cancel_move(Board* pboard, Pcoord* ppcoord,HistoryList* phistorylist);

/**
 * \fn void replay_move(Board* pboard, Pcoord* ppcoord)
 * \brief Add a previously withdrawn point to the Board.
 *
 * \param pboard Pointer to the Board being played.
 * \param ppcoord Pointer to pointer to replayed coordinates.
 */
void replay_move(Board* pboard, Pcoord* ppcoord,HistoryList* phistorylist);

#endif

