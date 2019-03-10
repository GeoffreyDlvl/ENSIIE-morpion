#ifndef HISTORIQUE_H
#define HISTORIQUE_H
/**
 * \file historique.h
 * \brief Records player moves during a game.
 * \authors Geoffrey DELVAL, Rémi GUIJARRO ESPINOSA, Gabriel MORAN, Clément PERESSE
 * \version lot_a
 * \date 03.2019
 *
 * Represents plateau.h upper layer. 
 * This class records player moves and allows to cancel or replay a move.
 *
 */

#include "plateau.h"

/**
 * \fn int play_move(Board* pboard, Pcoord pcoord)
 * \brief Add a point on the board.
 *
 * \param pboard Pointer to the board being played.
 * \param pcoord Pointer to selected coordinates.
 * \return 1 if point successfully added, 0 otherwise.
 */
int play_move(Board* pboard, Pcoord pcoord);
/**
 * \fn void cancel_move(Board* pboard, Pcoord pcoord)
 * \brief Withdraw a point from the board.
 *
 * \param pboard Pointer to the board being played.
 * \param ppcoord Pointer to pointer to canceled coordinates.
 */
void cancel_move(Board* pboard, Pcoord* ppcoord);
/**
 * \fn void replay_move(Board* pboard, Pcoord* ppcoord)
 * \brief Add a previously withdrawn point to the board.
 *
 * \param pboard Pointer to the board being played.
 * \param ppcoord Pointer to pointer to replayed coordinates.
 */
void replay_move(Board* pboard, Pcoord* ppcoord);

#endif

