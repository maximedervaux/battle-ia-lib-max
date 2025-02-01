#include "battle_c.h"
#include "unistd.h"
#include "math.h"
#include <ncurses.h>

int effectuer_tir(BC_Connection *connection, int angle) {
    float angle_radian = angle * (M_PI / 180);
    BC_ShootResult result = bc_shoot(connection, angle_radian);
    printf("TIR à angle %.2f radian (%d degrés)\n", angle_radian, angle);
    if (result.success) {
        printf("  Tir réussi !\n");
        if (result.target_destroyed) {
            printf("  L'ennemi a été détruit ! (ID cible : %lu)\n", result.target_id);
        } else {
            printf("  Dégâts infligés : %lu points (ID cible : %lu)\n", result.damage_points, result.target_id);
        }
    } else {
        printf("  Échec du tir.\n");
        switch (result.fail_reason) {
            case COOLDOWN:
                printf("  Le tir est en attente (cooldown).\n");
                break;
            case MISS:
                printf("  Le tir a échoué (miss).\n");
                break;
            case UNKNOWN:
            default:
                printf("  Raison inconnue de l'échec.\n");
        }
    }
    return result.success;
}

void se_deplacer(BC_Connection *connection, float speed_x, float speed_y) {
    bc_set_speed(connection, speed_x, speed_y, 0.0);
    fflush(stdout);
}

void deplacer_char(BC_Connection *connection) {
    initscr();
    timeout(0);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int key;
    float speed_x = 0.0, speed_y = 0.0;

    while (1) {
        key = getch();
        switch (key) {
            case KEY_UP:
                speed_y = -5.0;
                break;
            case KEY_DOWN:
                speed_y = 5.0;
                break;
            case KEY_LEFT:
                speed_x = -5.0;
                break;
            case KEY_RIGHT:
                speed_x = 5.0;
                break;
            case 'z':
                effectuer_tir(connection, 0);
                break;
            case 'a':
                speed_y = 0.0;
                speed_x = 0.0;
                break;
        }
        se_deplacer(connection, speed_x, speed_y);
        usleep(100000);
    }

    endwin();
}

int main() {
    BC_Connection *connection = bc_connect("5.135.136.236", 8080);
    if (!connection) {
        printf("Erreur : Impossible de se connecter au serveur\n");
        return 1;
    }
    printf("Connecté au serveur avec succès !\n");

    while (1) {
        deplacer_char(connection);
        sleep(1);
    }

    return 0;
}