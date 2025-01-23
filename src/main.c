#include "battle_c.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

void afficher_infos_player(BC_Connection *connection) {
    BC_PlayerData monPlayer = bc_get_player_data(connection);
    printf("ID : %d\n", monPlayer.id);
    printf("Health : %d\n", monPlayer.health);
    printf("Armor : %d\n", monPlayer.armor);
    printf("Score : %d\n", monPlayer.score);
    printf("Position x: %d , y: %d\n", monPlayer.position.x, monPlayer.position.y);
}


void se_deplacer(BC_Connection *connection, float speed_x, float speed_y, float speed_z) {
    bc_set_speed(connection, speed_x, speed_y, speed_z);
    printf("Vitesse définie : (%.2f, %.2f, %.2f)\n", speed_x, speed_y, speed_z);
}

void radar_ping(BC_Connection *connection) {
    BC_List *objects = bc_radar_ping(connection);
    while (objects) {
        BC_MapObject *object = (BC_MapObject *)bc_ll_value(objects);
        printf("Objet détecté : ID=%d, Type=%d, Position=(%.2f, %.2f)\n",
               object->id,
               object->type,
               object->position.x,
               object->position.y);
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

    BC_WorldInfo info = bc_get_world_info(connection);

    afficher_infos_player(connection);

    printf("Déplacement du joueur...\n");
    se_deplacer(connection, 0.0, 0.0, 0.0);


    afficher_infos_player(connection);

	int angle = 0;
	int angle_increment = 1;
	int cible_trouvee = 0;

	while (!cible_trouvee) {
    	sleep(3);
   		float angle_radian = angle * (3.14159 / 180);
    	BC_ShootResult test = bc_shoot(connection, angle_radian);
    	printf("TIR à angle %.2f radian (%d degrés) : %d\n", angle_radian, angle, test.success);

    	if (test.success) {
        	cible_trouvee = 1;
        	printf("Cible trouvée à angle %.2f radian (%d degrés) ! Bombardement en cours...\n", angle_radian, angle);


       	 while (test.success) {
            sleep(3);
            test = bc_shoot(connection, angle_radian);
            printf("BOMBARDEMENT à angle %.2f radian : %d\n", angle_radian, test.success);
        }

        printf("La cible détruite ou hors de portée!\n");
    }

   	 angle += angle_increment;
   	 if (angle >= 360) {
   	     angle -= 360;
   	 }
	}

    //printf("Analyse radar...\n");
    //radar_ping(connection);


	afficher_infos_player(connection);
    return 0;
}