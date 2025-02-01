//
// Created by Maxime Dervaux on 30/01/2025.
//


#include "tir.h"
#include "stdio.h"
#include "math.h"

// Fonction pour effectuer un tir à un angle donné (en degrés)
int effectuer_tir(BC_Connection *connection, int angle) {
    float angle_radian = angle * (M_PI / 180);  // Conversion de l'angle en radians
    BC_ShootResult result = bc_shoot(connection, angle_radian);
    printf("TIR à angle %.2f radian (%d degrés) : %d\n", angle_radian, angle, result.success);
    return result.success;
}