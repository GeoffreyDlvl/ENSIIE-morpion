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

struct playedMove
{
	Pcoord* coord;
	struct playedMove* PpreviousPlayedMove;
	struct playedMove* PnextPlayedMove;
};

typedef struct historyList
{
	size_t moves;
	struct playedMove* PfirstMove;
	struct playedMove* PlastPlayedMove;
	struct playedMove* PlastSavedMove;
} HistoryList;

/**
 * \fn bool play_move(Board* pboard, Pcoord pcoord)
 * \brief Add a point on the Board.
 *
 * \param pboard Pointer to the Board being played.
 * \param pcoord Pointer to selected coordinates.
 * \return true if point successfully added, false otherwise.
 */
bool play_move(Board* pboard, Pcoord pcoord);

/**
 * \fn void cancel_move(Board* pboard, Pcoord* ppcoord)
 * \brief Withdraw a point from the Board.
 *
 * \param pboard Pointer to the Board being played.
 * \param ppcoord Pointer to pointer to canceled coordinates.
 */
void cancel_move(Board* pboard, Pcoord* ppcoord);

/**
 * \fn void replay_move(Board* pboard, Pcoord* ppcoord)
 * \brief Add a previously withdrawn point to the Board.
 *
 * \param pboard Pointer to the Board being played.
 * \param ppcoord Pointer to pointer to replayed coordinates.
 */
void replay_move(Board* pboard, Pcoord* ppcoord);

#endif

