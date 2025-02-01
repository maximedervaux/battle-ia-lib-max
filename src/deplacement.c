//
// Created by Maxime Dervaux on 30/01/2025.
//
#include "deplacement.h"
#include "stdio.h"
#include "math.h"
#include "unistd.h"
#include "tools.h"

void se_deplacer(BC_Connection *connection, float speed_x, float speed_y) {
    bc_set_speed(connection, speed_x, speed_y, 0.0);
    printf("Vitesse définie : (%.2f, %.2f)\n", speed_x, speed_y);
    fflush(stdout);
}

void aller_a_position_specifique(BC_Connection *connection, BC_PlayerData *player, float destination_x, float destination_y) {
    float vitesse_max = 10.0;
    float seuil_arret = 1.0;
    float seuil_deceleration = 15.0;

    while (calculer_distance(player->position.x, player->position.y, destination_x, destination_y) > seuil_arret) {
        *player = bc_get_player_data(connection);
        float distance_restante = calculer_distance(player->position.x, player->position.y, destination_x, destination_y);
        float vitesse_actuelle = (distance_restante < seuil_deceleration) ? fmax(1.0, vitesse_max * (distance_restante / seuil_deceleration)) : vitesse_max;

        float speed_x = (player->position.x < destination_x) ? vitesse_actuelle : (player->position.x > destination_x) ? -vitesse_actuelle : 0;
        float speed_y = (player->position.y < destination_y) ? vitesse_actuelle : (player->position.y > destination_y) ? -vitesse_actuelle : 0;

        se_deplacer(connection, speed_x, speed_y);
        sleep(1);
    }

    se_deplacer(connection, 0.0, 0.0);
    printf("Bot arrêté à la destination (%.2f, %.2f)\n", destination_x, destination_y);
}