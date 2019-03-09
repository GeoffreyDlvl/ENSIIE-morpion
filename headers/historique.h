#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include "plateau.h"

int play_move(Board* pboard, Pcoord pcoord);
void cancel_move(Board* pboard, Pcoord* ppcoord);
void replay_move(Board* pboard, Pcoord* ppcoord);

#endif

