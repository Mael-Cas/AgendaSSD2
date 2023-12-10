/*
    Projet TI301 - Algorithmique et structures de données
    Par : Maël CASTELLAN - Doryan DENIS - Rémi DESJARDINS
    L2 - GROUPE A - EFREI PARIS
*/

#include "list_value.h"


//
// Created by Rémi Desjardins on 24/10/2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


t_level_list_value* createValueLevelList(){
    t_level_list_value *list = (t_level_list_value*)malloc(sizeof(t_level_list_value));
    list->level = 0;
    list->maxlevel = MAX_LEVEL_VALUE;
    list->heads = create_cell_value(MAX_LEVEL_VALUE, -1); // -1 pour la cellule en tête
    return list;
}

void InsertValueLevelList(t_level_list_value *list, int value, int head_level) {
    t_cell_value *update[MAX_LEVEL_VALUE + 1];
    t_cell_value *current = list->heads;

    // Commencer au niveau le plus haut de la liste et descendre
    for (int i = list->level; i >= 0; i--) {
        while (current->levels[i] != NULL && current->levels[i]->value < value) {
            current = current->levels[i];
        }
        update[i] = current;
    }

    current = current->levels[0];

    // Si current est NULL, on a atteint la fin du niveau
    // Si la valeur de current n'est pas égal à value, alors, nous avons trouvé l'endroit où insérer
    if (current == NULL || current->value != value) {
        int rlevel = head_level;
        // Si rlever est plus grand que le nombre de niveaux de la liste current, on initialise update avec des pointeurs sur les heads
        if (rlevel > list->level) {
            for (int i = list->level + 1; i <= rlevel; i++) {
                update[i] = list->heads;
            }
            // Mettre à jour la liste des niveaux
            list->level = rlevel;
        }

        // Créer une nouvelle cellule avec le bon niveau
        t_cell_value* new_cell = create_cell_value(rlevel, value);

        // Insérer la cellule
        for (int i = 0; i <= rlevel; i++) {
            new_cell->levels[i] = update[i]->levels[i];
            update[i]->levels[i] = new_cell;
        }
        // printf("Successfully inserted value %d at level %d\n", value, rlevel);
    }

}

void displayValueLevelList(t_level_list_value* list) {
    printf("\nDisplaying Level list:\n");
    for (int i = 0; i <= list->level; i++) {
        t_cell_value *temp = list->heads->levels[i];
        printf("[list head_%d @-]-->", i);
        while (temp != NULL) {
            printf("[ %d|@]-->", temp->value);
            temp = temp->levels[i];
        }
        printf(" NULL\n");

    }

}

void displayOneLevelValue(t_level_list_value* list, int level){
    printf("\nDisplaying One Level of the list:\n");
    t_cell_value *temp = list->heads->levels[level];
    printf("[list head_%d @-]-->", level);
    while (temp != NULL) {
        printf("[ %d|@]-->", temp->value);
        temp = temp->levels[level];
    }
    printf(" NULL\n");

}

// Fonction pour chercher une valeur rapidement
t_cell_value* searchInValueList(t_level_list_value* list, int value){
    t_cell_value* current = list->heads;

    // Commencer au niveau le plus haut de la liste
    for(int i = list->level; i >= 0; i--){
        // Aller plus loin dans la liste tant que la va&leur précédente est plus petite
        while(current->levels[i] && current->levels[i]->value < value){
            current = current->levels[i];
        }
    }

    //On atteint le niveau 0 et on le parcours
    current = current->levels[0];
    // Si la valeur de la cellule courante est la valeur que l'on cherche, on a trouvé notre cible
    if(current && current->value == value){
        return current;
    }

    return NULL; // pas trouvé

}

t_cell_value * classicSearchInValueList(t_level_list_value* list, int val) {
    t_cell_value* current = list->heads->levels[0];
    while (current != NULL) {
        if (current->value == val) {
            return current;  // Élément trouvé
        }
        current = current->levels[0];  // Passer à l'élément suivant
    }

    return NULL;  // Élément non trouvé
}


// Fonction pour supprimer une cellule
void deleteValueNode(t_level_list_value* list, int value) {
    t_cell_value *current = list->heads;
    t_cell_value **update = malloc((list->maxlevel + 1) * sizeof(t_cell_value*));

    // Commencer au plus haut niveau de la liste
    for (int i = list->level; i >= 0; i--) {
        while (current->levels[i] != NULL && current->levels[i]->value < value) {
            current = current->levels[i];
        }
        update[i] = current;
    }

    // Atteindre le niveau 0
    current = current->levels[0];

    // Si on trouve la cellule et qu'elle a la bonne valeur
    if (searchInValueList(list, current->value)) {
        // Commencer du niveau le plus bas et supprimer toutes les cellules des niveaux plus haut
        for (int i = 0; i <= list->level; i++) {
            // If at level i, the next node is not the target node, break the loop.
            if (update[i]->levels[i] != current)
                break;

            // Enlever le pointeur de la cellule supprimée
            update[i]->levels[i] = current->levels[i];
        }

        // Enlever les niveaux qui ne sont plus utilisés
        while (list->level > 0 && list->heads->levels[list->level] == NULL) {
            list->level--;
        }

        printf("Successfully deleted value %d\n", value);
        free(current);
    } else {
        printf("Value %d not found\n", value);
    }
    free(update);
}

void freeValueLevelList(t_level_list_value *list) {
    if (list != NULL) {
        // Si list->heads est un tableau de pointeurs
        for (int i = 0; i <= list->maxlevel; i++) {
            t_cell_value *current = &list->heads[i];
            while (current != NULL) {
                t_cell_value *temp = current;
                current = current->levels[0]; // Supposant que vous voulez suivre le niveau le plus bas
                free(temp);
            }
        }
        free(list->heads); // Libérer le tableau lui-même

        // Libérer la liste
        free(list);
    }
}

