//
// Created by Maxime Dervaux on 01/02/2025.
//

#ifndef TOOLS_H
#define TOOLS_H
#include "battle_c.h"


BC_Vector3 position_joueur(BC_Connection *connection, BC_PlayerData *player);
float calculer_distance(float x1, float y1, float x2, float y2) ;
void afficher_infos_monde(BC_Connection *connection, BC_WorldInfo *world_info) ;
void afficher_infos_player(BC_Connection *connection, BC_PlayerData *player) ;
void afficher_objets_radar(BC_Connection *connection) ;
void afficher_points_player(BC_Connection *connection, BC_PlayerData *player) ;
#endif //TOOLS_H
