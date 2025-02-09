# README - Battle Code Char Bot

## Description
Ce projet implémente un char automatisé pour un jeu dans le cadre de la formation JUNIA ISEN. Le char est capable de se déplacer de manière autonome en cherchant les différents boosts, d'identifier les ennemis les plus proches et de tirer dans leur direction. Le tout est géré via des threads pour assurer la réactivité de notre bot. La stratégie adoptée est de prioriser les déplacements rapides vers les boosts pour assurer des points et de tirer vers le char le plus proche toutes les 3 secondes pour éventuellement récupérer des points supplémentaires.
## Organisation du Projet

Le projet est composé des fichiers suivants :

- **main.c** : Contient la boucle principale et la gestion des threads.
- **battle_c.h** : Bibliothèque de connexion au serveur du jeu.
- **deplacement.h / deplacement.c** : Gère les déplacements du char.
- **tir.h / tir.c** : Implémente la logique de tir.
- **radar.h / radar.c** : Gère la détection des objets et ennemis via un radar.
- **tools.h / tools.c** : Contient des fonctions utilitaires (calculs de distance, affichage des informations, etc.).

## Fonctionnalités Principales

### 1. Connexion au Serveur
Dans `main.c`, le char se connecte au serveur en utilisant :
```c
BC_Connection *connection = bc_connect("5.135.136.236", 8080);
```
Si la connexion échoue, le programme se termine.

### 2. Détection et Déplacement vers les Boosts
Le char scanne l'environnement à la recherche des boosts de puissance et se déplace vers le plus proche en utilisant :
```c
BC_MapObject *boost_proche = trouver_boost_proche(connection, player.position, player.id);
aller_a_position_specifique(connection, &player, boost_proche->position.x, boost_proche->position.y);
```

### 3. Détection et Tir sur les Ennemis
Un thread dédié (`thread_tir`) recherche en continu l'ennemi le plus proche et tire automatiquement toutes les 3 secondes :
```c
BC_MapObject *ennemi_proche = trouver_ennemi_proche(connection, player->position, player->id);
```
Puis, si un ennemi est trouvé, il tire dans sa direction :
```c
effectuer_tir(connection, angle_tir);
```

### 4. Radar et Affichage des Informations
Le radar scanne périodiquement la carte pour identifier les objets et ennemis présents. Les informations du joueur et du monde sont affichées à l'écran.

Exemple d'affichage :
```c
void afficher_infos_player(BC_Connection *connection, BC_PlayerData *player) {
    *player = bc_get_player_data(connection);
    printf("ID : %lu\n", player->id);
    printf("Health : %d\n", player->health);
    printf("Position du joueur -> x: %.2f, y: %.2f\n", player->position.x, player->position.y);
}
```

## Compilation et Exécution
### Compilation
Utiliser `ninja` pour compiler le programme 

### Exécution
Lancer l'exécutable généré :
```sh
./build/battle_c_bot
```

## Améliorations Possibles
- **Moins de temps d'arret sur les boosts** : Faire en sorte que quand le boost a etait pris le char reparte et ne s'arrete pas
- **Amélioration de l'intelligence du tir** : Optimiser l'angle de tir en fonction de la vitesse et de la trajectoire de l'ennemi.

