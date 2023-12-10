/*
    Projet TI301 - Algorithmique et structures de données
    Par : Maël CASTELLAN - Doryan DENIS - Rémi DESJARDINS
    L2 - GROUPE A - EFREI PARIS

    list.h/.c : Contient toutes les fonctions qui concerne les listes à niveaux ainsi que les structures
*/

#ifndef AGENDASSD2_LIST_H
#define AGENDASSD2_LIST_H

#include "cell.h"

// Structure de la liste à niveaux
typedef struct s_level_list
{
    int level; // Niveau maximum logique
    int maxlevel; // Niveau maximum physique
    t_cell *heads; // Contient les pointeurs vers le noeud d'en-tête
} t_level_list;




// Fonctions demandées dans le projet
t_level_list* createLevelList();

// Fonctions d'affichage
void displayLevelList(t_level_list* list);
void displayOneLevel(t_level_list*, int);

// Fonctions de recherche
t_cell* searchInList(t_level_list*, Contact*);
t_cell* classicSearchInList(t_level_list*, Contact*);

// Fonctions de suppression et de libération de mémoire
void deleteNode(t_level_list*, Contact*);
void freeLevelList(t_level_list*);


// Fonctions pour l'auto-complétion
Contact* autocompleteSearch(t_level_list *);
int showSuggestions(t_level_list *, char *);
Contact* chooseContact(t_level_list *, char*, int);

// Fonctions pour l'insertion
void InsertLevelList(t_level_list *list, Contact *, int head_level);
int determineLevel(t_level_list*, Contact*);
void insertContact(t_level_list*, Contact*);

// Fonctions pour créer la liste à 1 000 contacts
char** readCsvFile(const char*, int*, char);
Contact** generateContacts(char**, char**, int);
void freeStringArray(char**, int);
void createThousandContactList(t_level_list*);
void displayLoadingBar(int, int);

#endif //AGENDASSD2_LIST_H
