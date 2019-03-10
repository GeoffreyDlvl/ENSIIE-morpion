#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include "plateau.h"

/**
 * \file historique.h
 * \brief plateau.h overlay
 **/

int play_move(Board* pboard, Pcoord pcoord);
void cancel_move(Board* pboard, Pcoord* ppcoord);
void replay_move(Board* pboard, Pcoord* ppcoord);

#endif

