#include <pthread.h>
#include "battle_c.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "math.h"
#include "deplacement.h"
#include "tir.h"
#include "tools.h"
#include "radar.h"
#include "main.h"

void *thread_tir(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    BC_Connection *connection = data->connection;
    BC_PlayerData *player = data->player;

    while (1) {
        sleep(3); // Tir toutes les 3 secondes

        *player = bc_get_player_data(connection);
        BC_MapObject *ennemi_proche = trouver_ennemi_proche(connection, player->position, player->id);

        if (ennemi_proche) {
            float dx = ennemi_proche->position.x - player->position.x;
            float dy = ennemi_proche->position.y - player->position.y;
            int angle_tir = (int)(atan2(dy, dx) * (180.0 / M_PI));
            if (angle_tir < 0) angle_tir += 360;

            effectuer_tir(connection, angle_tir);
            printf("🔫 Tir effectué à %d° !\n", angle_tir);
        }
    }
    return NULL;
}

int main() {
    BC_Connection *connection = bc_connect("5.135.136.236", 8080);
    if (!connection) {
        printf("Erreur : Impossible de se connecter au serveur\n");
        return 1;
    }

    printf("Connecté au serveur avec succès !\n");

    BC_PlayerData player = bc_get_player_data(connection);

    // Lancer le thread pour le tir
    pthread_t tir_thread;
    ThreadData data = {connection, &player};
    pthread_create(&tir_thread, NULL, thread_tir, &data);

    // Boucle principale : Déplacement vers les boosts
    while (1) {
        player = bc_get_player_data(connection);
        BC_MapObject *boost_proche = trouver_boost_proche(connection, player.position, player.id);

        if (boost_proche) {
            aller_a_position_specifique(connection, &player, boost_proche->position.x, boost_proche->position.y);
        }

        afficher_points_player(connection, &player);
        sleep(1);
    }

    pthread_join(tir_thread, NULL);

    return 0;
}