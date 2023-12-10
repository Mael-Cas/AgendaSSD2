/*
    Projet TI301 - Algorithmique et structures de données
    Par : Maël CASTELLAN - Doryan DENIS - Rémi DESJARDINS
    L2 - GROUPE A - EFREI PARIS
    save.h/.c : Contient les fonctiosn de sauvegarde des rendez-vous
*/

#ifndef AGENDASSD2_SAVE_H
#define AGENDASSD2_SAVE_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "list.h"


void saveToFile(t_level_list*, const char* );
void loadFromFile(t_level_list *, const char *);


#endif //AGENDASSD2_SAVE_H
