//
// Created by Rémi Desjardins on 24/10/2023.
//

#include "cell.h"
#include <stdlib.h>
#include <stdio.h>


// Fonction pour créer une nouvelle cellule
t_cell* create_cell(int level){
    t_cell* new_cell = (t_cell*)malloc(sizeof(t_cell));
    new_cell->contact = NULL;
    for (int i = 0; i <= level; i++) {
        new_cell->levels[i] = NULL;
    }
    return new_cell;
}