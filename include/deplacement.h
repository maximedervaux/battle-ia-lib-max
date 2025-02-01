//
// Created by Maxime Dervaux on 30/01/2025.
//

#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H
#include "battle_c.h"


void se_deplacer(BC_Connection *connection, float speed_x, float speed_y);
void aller_a_position_specifique(BC_Connection *connection, BC_PlayerData *player, float destination_x, float destination_y) ;

#endif //DEPLACEMENT_H
