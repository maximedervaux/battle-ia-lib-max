#include "battle_c.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h" // Pour sleep()
#include "math.h"
#include "deplacement.h"
#include "tir.h"
#include "tools.h"
#include "radar.h"


int main() {
    BC_Connection *connection = bc_connect("5.135.136.236", 8080);
    if (!connection) {
        printf("Erreur : Impossible de se connecter au serveur\n");
        fflush(stdout);
        return 1;
    }

    printf("Connecté au serveur avec succès !\n");
    fflush(stdout);

    BC_WorldInfo world_info;
    afficher_infos_monde(connection, &world_info);

    BC_PlayerData player;
    afficher_infos_player(connection, &player);

    float destination_x = 96.0;
    float destination_y = 70.0;

    aller_a_position_specifique(connection, &player, destination_x, destination_y);

    while (1) {
        player = bc_get_player_data(connection);  // Mise à jour de la position du joueur

        BC_MapObject *ennemi_proche = trouver_ennemi_proche(connection, player.position,player.id);

        while (ennemi_proche) {
            float dx = ennemi_proche->position.x - player.position.x;
            float dy = ennemi_proche->position.y - player.position.y;


            int angle_tir = (int)(atan2(dy, dx) * (180.0 / M_PI));
            if (angle_tir < 0) angle_tir += 360;

            effectuer_tir(connection, angle_tir);

            sleep(3);

            player = bc_get_player_data(connection);
            ennemi_proche = trouver_ennemi_proche(connection, player.position,player.id);
        }

        sleep(1);
    }

    return 0;
}
