#include "battle_c.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

// Afficher les informations du joueur
void afficher_infos_player(BC_Connection *connection) {
    BC_PlayerData monPlayer = bc_get_player_data(connection);
    printf("ID : %d\n", monPlayer.id);
    printf("Health : %d\n", monPlayer.health);
    printf("Armor : %d\n", monPlayer.armor);
    printf("Score : %d\n", monPlayer.score);
    printf("Position x: %.2f , y: %.2f\n", monPlayer.position.x, monPlayer.position.y);
}


void se_deplacer(BC_Connection *connection, float speed_x, float speed_y, float speed_z) {
    bc_set_speed(connection, speed_x, speed_y, speed_z);
    printf("Vitesse définie : (%.2f, %.2f, %.2f)\n", speed_x, speed_y, speed_z);
}

void radar_ping(BC_Connection *connection) {
    BC_List *objects = bc_radar_ping(connection);
    while (objects) {
        BC_MapObject *object = (BC_MapObject *)bc_ll_value(objects);
        printf("Objet détecté : ID=%d, Type=%d, Position=(%.2f, %.2f, %.2f)\n",
               object->id,
               object->type,
               object->position.x,
               object->position.y,
               object->position.z);
        objects = bc_ll_next(objects);
    }
}


int main() {
    BC_Connection *connection = bc_connect("5.135.136.236", 8080);
    if (!connection) {
        printf("Erreur : Impossible de se connecter au serveur\n");
        return 1;
    }
    printf("Connecté au serveur avec succès !\n");

    afficher_infos_player(connection);

    printf("Déplacement du joueur...\n");
    se_deplacer(connection, 1.0f, 0.0f, 0.0f);  // Déplacer vers la droite


    printf("Analyse radar...\n");
    radar_ping(connection);


    sleep(2);

    return 0;
}