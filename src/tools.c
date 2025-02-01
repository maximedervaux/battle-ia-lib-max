//
// Created by Maxime Dervaux on 01/02/2025.
//

#include "math.h"
#include "tools.h"
#include <stdio.h>

BC_Vector3 position_joueur(BC_Connection *connection, BC_PlayerData *player) {
    *player = bc_get_player_data(connection);
    return player->position;
}



void afficher_infos_monde(BC_Connection *connection, BC_WorldInfo *world_info) {
    *world_info = bc_get_world_info(connection);
    printf("Dimensions de la carte : %lux%lu\n", world_info->map_x, world_info->map_y);
    printf("Nombre de joueurs : %u\n", world_info->player_count);
    printf("Auto-shoot activé : %s\n", world_info->auto_shoot_enabled ? "Oui" : "Non");
    printf("Radar activé : %s\n", world_info->radar_enabled ? "Oui" : "Non");
}

void afficher_infos_player(BC_Connection *connection, BC_PlayerData *player) {
    *player = bc_get_player_data(connection);
    printf("ID : %d\n", player->id);
    printf("Health : %d\n", player->health);
    printf("Armor : %d\n", player->armor);
    printf("Score : %d\n", player->score);
    printf("Position du joueur -> x: %.2f, y: %.2f\n", player->position.x, player->position.y);
}

