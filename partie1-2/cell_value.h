/*
    Projet TI301 - Algorithmique et structures de données
    Par : Maël CASTELLAN - Doryan DENIS - Rémi DESJARDINS
    L2 - GROUPE A - EFREI PARIS
    cell_value.h/.c : Contient les fonctions et structures pour la cellule en int
*/

#ifndef AGENDASSD2_CELL_VALUE_H
#define AGENDASSD2_CELL_VALUE_H
#define MAX_LEVEL_VALUE 30

// Structure pour la cellule avec un int
typedef struct s_cell_value {
    int value;
    struct s_cell_value *levels[MAX_LEVEL_VALUE+ 1]; // Contient les pointeurs des différents niveaux
} t_cell_value;

// Fonctions pour les cellules
t_cell_value* create_cell_value(int level, int value);
void free_cell(t_cell_value*);
#endif //AGENDASSD2_CELL_VALUE_H
