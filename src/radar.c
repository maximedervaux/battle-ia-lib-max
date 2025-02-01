#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "radar.h"
#include "tools.h"

BC_MapObject *trouver_ennemi_proche(BC_Connection *connection, BC_Vector3 position_joueur, int id_joueur) {
    size_t count;
    BC_List *objets = bc_radar_ping(connection);

    if (!objets) {
        return NULL;
    }

    BC_MapObject **ennemis = (BC_MapObject **)malloc(count * sizeof(BC_MapObject *));
    size_t index = 0;

    BC_List *node;
    for (node = objets; node != NULL; node = bc_ll_next(node)) {
        BC_MapObject *objet = (BC_MapObject *)bc_ll_value(node);
        if (objet->type == OT_PLAYER && objet->id != id_joueur) {  // Exclure le joueur lui-même
            ennemis[index++] = objet;
        }
    }

    if (index == 0) {
        free(ennemis);
        bc_ll_free(objets);
        return NULL;
    }

    printf("Ennemis détectés :\n");
    for (size_t i = 0; i < index; i++) {
        printf("  Ennemi %zu - Position: (%.2f, %.2f), ID: %llu\n",
                i + 1, ennemis[i]->position.x, ennemis[i]->position.y, ennemis[i]->id);
    }

    for (size_t i = 0; i < index - 1; i++) {
        for (size_t j = i + 1; j < index; j++) {
            float dist1 = calculer_distance(position_joueur.x, position_joueur.y, ennemis[i]->position.x, ennemis[i]->position.y);
            float dist2 = calculer_distance(position_joueur.x, position_joueur.y, ennemis[j]->position.x, ennemis[j]->position.y);

            if (dist1 > dist2) {
                BC_MapObject *temp = ennemis[i];
                ennemis[i] = ennemis[j];
                ennemis[j] = temp;
            }
        }
    }

    BC_MapObject *ennemi_proche = ennemis[0];
    printf("\nEnnemi le plus proche :\n");
    printf("  Position: (%.2f, %.2f), ID: %llu\n", ennemi_proche->position.x, ennemi_proche->position.y, ennemi_proche->id);

    free(ennemis);
    bc_ll_free(objets);

    return ennemi_proche;
}