/*
    Projet TI301 - Algorithmique et structures de données
    Par : Maël CASTELLAN - Doryan DENIS - Rémi DESJARDINS
    L2 - GROUPE A - EFREI PARIS
*/

// Inclusion des en-têtes nécessaires
#include <stdio.h>
#include "menu.h"
#include "list.h"


int main() {
    int option, part;
    printf("Which part do you wanna test ? \n");
    printf("1. Part 1 and 2\n2. Part 3\n");
    while (1) {
        printf("Please, enter a value between 1 and 2: ");
        if (scanf("%d", &part) == 1 && (part == 1 || part == 2)) {
            // Si la saisie est correcte, sortir de la boucle
            break;
        } else {
            // Vider le buffer d'entrée
            clearInputBuffer();
            printf("Invalid input. \n");
        }
    }

    switch (part) {
        case 1 :{
            t_level_list_value* list = createValueLevelList();
            printf("Welcome to the test of part 1/2\n");
            do {
                printMenu1();
                scanf(" %d", &option);
                clearInputBuffer();
                executeOption1(list, option);
            }while(option != 7);
            break;
        }
        case 2:{
            printf("Welcome to the test of part 3\n");
            t_level_list* list = createLevelList();
            do {
                printMenu();
                scanf(" %d", &option);
                clearInputBuffer();
                executeOption(list, option);
            } while (option != 11);
            freeLevelList(list);

            break;
        }
    }


    // Libération de la mémoire avant de quitter

    return 0;
}
