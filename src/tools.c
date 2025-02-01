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

float calculer_distance(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
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

void afficher_objets_radar(BC_Connection *connection) {
    size_t count;
    BC_List *objets = bc_radar_ping(connection);

    if (!objets) {
        printf("Aucun objet détecté par le radar.\n");
        return;
    }
    BC_List *node;
    for (node = objets; node != NULL; node = bc_ll_next(node)) {
        BC_MapObject *objet = (BC_MapObject *)bc_ll_value(node);
        printf("Objet détecté : Type = %d, Position = (%.2f, %.2f)\n",
               objet->type, objet->position.x, objet->position.y);
    }

    bc_ll_free(objets);  // Libérer la mémoire allouée pour la liste
}