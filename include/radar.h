//
// Created by Maxime Dervaux on 01/02/2025.
//

#ifndef RADAR_H
#define RADAR_H

#include "battle_c.h"

BC_MapObject *trouver_ennemi_proche(BC_Connection *connection, BC_Vector3 position_joueur, int id_joueur);
BC_MapObject *trouver_boost_proche(BC_Connection *connection, BC_Vector3 position_joueur, int id_joueur) ;
#endif //RADAR_H
