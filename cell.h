/*
    Projet TI301 - Algorithmique et structures de données
    Par : Maël CASTELLAN - Doryan DENIS - Rémi DESJARDINS
    L2 - GROUPE A - EFREI PARIS
    cell.h/.c : Contient toutes les fonctions qui concernent les cellules de la liste à niveaux ainsi que la structure de celle-ci.
*/

#ifndef AGENDASSD2_CELL_H
#include "meeting.h"
#define AGENDASSD2_CELL_H

#define MAX_LEVEL 3

// Structure de la cellule
typedef struct s_cell {
    Contact *contact;
    struct s_cell *levels[MAX_LEVEL + 1]; // Contient les pointeurs des différents niveaux
} t_cell;

// Fonction pour créer une cellule
t_cell* create_cell(int level);

#endif //AGENDASSD2_CELL_H
