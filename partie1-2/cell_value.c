/*
    Projet TI301 - Algorithmique et structures de données
    Par : Maël CASTELLAN - Doryan DENIS - Rémi DESJARDINS
    L2 - GROUPE A - EFREI PARIS
*/

#include "cell_value.h"
#include <stdlib.h>
#include <stdio.h>


// Fonction pour créer une nouvelle cellule
t_cell_value* create_cell_value(int level, int value){
    t_cell_value* new_cell = (t_cell_value*)malloc(sizeof(t_cell_value));
    new_cell->value = value;
    for (int i = 0; i <= level; i++) {
        new_cell->levels[i] = NULL;
    }
    return new_cell;
}

void free_cell(t_cell_value *cell) {
    if (cell != NULL) {
        free(cell);
    }
}