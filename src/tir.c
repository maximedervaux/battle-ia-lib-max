#include "tir.h"
#include "stdio.h"
#include "math.h"

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
