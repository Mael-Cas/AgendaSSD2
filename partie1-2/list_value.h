/*
    Projet TI301 - Algorithmique et structures de données
    Par : Maël CASTELLAN - Doryan DENIS - Rémi DESJARDINS
    L2 - GROUPE A - EFREI PARIS
    list_value.h/.c : Contient les fonctions pour les listes à niveaux mais avec des valeurs int.
*/

#ifndef AGENDASSD2_LIST_VALUE_H
#define AGENDASSD2_LIST_VALUE_H

#include "cell_value.h"

// Structure de la liste à niveaux
typedef struct s_level_list_value
{
    int level;
    int maxlevel;
    t_cell_value *heads; // Contient les pointeurs vers le noeud d'en-tête
} t_level_list_value;



// Fonctions pour les listes à niveaux
t_level_list_value* createValueLevelList();
void InsertValueLevelList(t_level_list_value *, int, int);
void displayValueLevelList(t_level_list_value*);
void displayOneLevelValue(t_level_list_value *, int);
t_cell_value* searchInValueList(t_level_list_value*, int);
t_cell_value* classicSearchInValueList(t_level_list_value*, int);
void deleteValueNode(t_level_list_value*, int);
void freeValueLevelList(t_level_list_value*);

#endif //AGENDASSD2_LIST_VALUE_H
