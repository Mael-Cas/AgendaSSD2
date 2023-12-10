/*
    Projet TI301 - Algorithmique et structures de données
    Par : Maël CASTELLAN - Doryan DENIS - Rémi DESJARDINS
    L2 - GROUPE A - EFREI PARIS
    menu.h/.c : Contient les fonctions de menu pour les utilisateurs
*/

#ifndef AGENDASSD2_MENU_H
#define AGENDASSD2_MENU_H

#include "list.h"
#include "partie1-2/list_value.h"


// FOncitons pour le menu des parties 1 et 2
void printMenu1();
void executeOption1(t_level_list_value*, int);

//Fonctions pour le menu de la partie 3
void printMenu();
void executeOption(t_level_list *list, int option);

int randomInRange(int , int);
#endif //AGENDASSD2_MENU_H
