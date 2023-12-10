/*
    Projet TI301 - Algorithmique et structures de données
    Par : Maël CASTELLAN - Doryan DENIS - Rémi DESJARDINS
    L2 - GROUPE A - EFREI PARIS
*/


// Inclusion des en-têtes nécessaires
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Définitions de constantes pour la longueur maximale du nom et le nombre maximal de contacts
#define MAX_NAME_LENGTH 100
#define MAX_CONTACTS 1000

// Crée et initialise une nouvelle liste à niveaux
t_level_list* createLevelList(){
    // Allocation dynamique de la liste
    t_level_list *list = (t_level_list*)malloc(sizeof(t_level_list));
    // Initialisation du niveau actuel et du niveau maximum
    list->level = 0;
    list->maxlevel = MAX_LEVEL;
    // Création d'une cellule en tête pour chaque niveau
    list->heads = create_cell(MAX_LEVEL);
    return list; // Retourne la nouvelle liste
}

// Insère un contact dans la liste à un niveau spécifié
void InsertLevelList(t_level_list *list, Contact *newContact, int head_level) {
    t_cell *update[MAX_LEVEL + 1];
    t_cell *current = list->heads;

    // Trouve la position d'insertion pour chaque niveau
    for (int i = list->level; i >= 0; i--) {
        while (current->levels[i] != NULL && compareContact(current->levels[i]->contact, newContact) < 0 ) {
            current = current->levels[i];
        }
        update[i] = current;
    }

    current = current->levels[0];

    // Insère le nouveau contact si ce n'est pas un doublon
    if (current == NULL || compareContact(current->contact, newContact) != 0) {
        int rlevel = head_level;

        // Mise à jour du niveau de la liste si nécessaire
        if (rlevel > list->level) {
            for (int i = list->level + 1; i <= rlevel; i++) {
                update[i] = list->heads;
            }
            list->level = rlevel;
        }

        // Création et insertion de la nouvelle cellule
        t_cell* new_cell = create_cell(rlevel);
        new_cell->contact = newContact;
        for (int i = 0; i <= rlevel; i++) {
            new_cell->levels[i] = update[i]->levels[i];
            update[i]->levels[i] = new_cell;
        }
    }
}

// Affiche tous les niveaux de la liste
void displayLevelList(t_level_list* list) {
    printf("\nDisplaying Contact list:\n");
    // Parcourt chaque niveau et affiche les contacts
    for (int i = 0; i <= list->level; i++) {
        t_cell *temp = list->heads->levels[i];
        printf("[list head_%d @-]-->", i);
        while (temp != NULL) {
            printf("[");
            printContact(temp->contact);
            printf("|@]-->");
            temp = temp->levels[i];
        }
        printf(" NULL\n");
    }
}

// Affiche un niveau spécifique de la liste
void displayOneLevel(t_level_list* list, int level){
    printf("\nDisplaying One Level of the list:\n");
    t_cell *temp = list->heads->levels[level];
    printf("[list head_%d @-]-->", level);
    while (temp != NULL) {
        printf("[");
        printContact(temp->contact);
        printf("|@]-->");
        temp = temp->levels[level];
    }
    printf(" NULL\n");
}

// Recherche un contact dans la liste
t_cell* searchInList(t_level_list* list, Contact* contact){
    t_cell* current = list->heads;

    // Parcourt la liste à partir du niveau le plus élevé
    for(int i = list->level; i >= 0; i--){
        while(current->levels[i] && compareContact(current->levels[i]->contact, contact) < 0){
            current = current->levels[i];
        }
    }

    current = current->levels[0];

    // Retourne le contact s'il est trouvé
    if(current && compareContact(current->contact, contact) == 0){
        return current;
    }
    return NULL; // Contact non trouvé
}

// Recherche classique dans la liste (niveau 0 uniquement)
t_cell * classicSearchInList(t_level_list* list, Contact* contact) {
    t_cell* current = list->heads->levels[0];
    while (current != NULL) {
        if (current->contact == contact) {
            return current;  // Élément trouvé
        }
        current = current->levels[0];  // Passer à l'élément suivant
    }
    return NULL;  // Élément non trouvé
}

// Supprime un noeud (contact) de la liste
void deleteNode(t_level_list* list, Contact *contact) {
    t_cell* current = list->heads;
    t_cell **update = malloc((list->maxlevel + 1) * sizeof(t_cell*));

    // Trouve le noeud à supprimer
    for (int i = list->level; i >= 0; i--) {
        while (current->levels[i] != NULL && current->levels[i]->contact < contact) {
            current = current->levels[i];
        }
        update[i] = current;
    }

    current = current->levels[0];

    // Supprime le noeud si trouvé
    if (searchInList(list, current->contact)) {
        for (int i = 0; i <= list->level; i++) {
            if (update[i]->levels[i] != current)
                break;
            update[i]->levels[i] = current->levels[i];
        }

        // Ajuste le niveau de la liste si nécessaire
        while (list->level > 0 && list->heads->levels[list->level] == NULL) {
            list->level--;
        }

        free(current); // Libère la mémoire du noeud supprimé
    } else {
        printf("Contact not found");
    }

    free(update); // Libère la mémoire allouée pour le tableau update
}



Contact* autocompleteSearch(t_level_list *list) {


    if(list->heads->levels[0] == NULL){
        printf("No contact in the list. Press Enter.\n");
        return NULL;
    }
    char inputBuffer[100];
    int charCount = 0;

    printf("Enter the first 3 letters of the contact's name (press Enter to see suggestions):\n");
    while (charCount < 99 && (inputBuffer[charCount] = getchar()) != '\n') {
        charCount++;
    }

    if (charCount >= 3) {
        inputBuffer[charCount] = '\0';
        int numSuggestions = showSuggestions(list, inputBuffer);
        if (numSuggestions > 0) {
            return chooseContact(list, inputBuffer, numSuggestions);
        } else {
            printf("No suggestions available.\n");
            return NULL;
        }
    } else {
        printf("You need at least 3 characters !\n");
    }
    return NULL;
}




int showSuggestions(t_level_list* list, char* partialName) {
    for(int i = 0; partialName[i] != '\0'; i++){
        partialName[i] = tolower(partialName[i]);
    }

    t_cell *current = list->heads;
    int index = 1; // Commencez l'indexation à 1

    // Commencer au niveau le plus haut de la liste
    for(int i = list->level; i >= 0; i--) {
        while(current->levels[i] != NULL && strncmp(current->levels[i]->contact->last_name, partialName, strlen(partialName)) < 0) {
            current = current->levels[i];
        }
    }

    // On atteint le niveau 0 et on le parcourt
    current = current->levels[0];
    while (current != NULL) {
        if (strncmp(current->contact->last_name, partialName, strlen(partialName)) == 0) {
            printf("%d. ", index);
            printContact(current->contact);
            printf("\n");
            index++;
        }
        current = current->levels[0];
    }

    if (index == 1) { // Aucune suggestion trouvée
        printf("No match.\n");
    }
    return index - 1;
}

Contact* chooseContact(t_level_list *list, char *inputBuffer, int maxIndex) {
    int choice;
    do {
        clearInputBuffer();
        printf("\nEnter the number of the chosen contact (or 0 to exit):\n");
        if (scanf("%d", &choice) != 1) {
            // Gestion de l'erreur si l'utilisateur ne saisit pas un nombre
            printf("Please enter a valid number.\n");
            continue;
        }

        if (choice == 0) {
            return NULL;
        } else if (choice < 0 || choice > maxIndex) {
            printf("Please enter a number between 1 and %d.\n", maxIndex);
        } else {
            // Trouver et renvoyer le contact
            t_cell *current = list->heads->levels[0];
            for (int i = 1; current != NULL && i <= choice; i++, current = current->levels[0]) {
                if (i == choice) {
                    return current->contact;
                }
            }
        }
    } while (choice < 0 || choice > maxIndex);

    return NULL; // Si nous sortons de la boucle, quelque chose s'est mal passé
}


// Détermine le niveau auquel doit être inséré un contact
int determineLevel(t_level_list *list, Contact *contact) {
    int level = 0;

    // Convertir le nom du contact en minuscules pour la comparaison
    char contactNameLower[MAX_LEVEL + 1];
    strncpy(contactNameLower, contact->name, MAX_LEVEL);
    contactNameLower[MAX_LEVEL] = '\0';
    for (int i = 0; i < MAX_LEVEL && contactNameLower[i]; ++i) {
        contactNameLower[i] = tolower(contactNameLower[i]);
    }

    // On commence par le niveau le plus élevé et on descend
    for (int i = MAX_LEVEL; i > 0; --i) {
        int isDifferent = 0; // si on a trouvé une différence au niveau actuel

        // Parcourir la liste à ce niveau pour trouver une différence
        t_cell *current = list->heads->levels[i - 1];
        while (current != NULL) {
            char currentLetter = current->contact->name[i - 1];
            if (!currentLetter || tolower(currentLetter) != contactNameLower[i - 1]) {
                isDifferent = 1;
                break;
            }
            current = current->levels[i - 1];
        }

        // Si une différence est trouvée au niveau actuel, c'est le niveau d'insertion
        if (isDifferent) {
            level = i;
            break;
        }
    }

    return level;
}




void insertContact(t_level_list* list, Contact* contact){
    InsertLevelList(list, contact,determineLevel(list, contact));
}






// Fonction pour afficher la barre de chargement
void displayLoadingBar(int current, int total) {
    float progress = (float)current / total;
    int barWidth = 50; // Largeur de la barre de chargement

    printf("[");
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) printf("=");
        else if (i == pos) printf(">");
        else printf(" ");
    }
    printf("] %d%%\r", (int)(progress * 100));
    fflush(stdout); // Pour s'assurer que la sortie est affichée immédiatement
}



// Création de la liste à 1000 contacts
char** readCsvFile(const char* filePath, int* count, char delimiter) {
    FILE* file = fopen(filePath, "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    }

    char** array = malloc(MAX_CONTACTS * sizeof(char*));
    char line[MAX_NAME_LENGTH];
    *count = 0;

    while (fgets(line, MAX_NAME_LENGTH, file) && *count < MAX_CONTACTS) {
        char* token = strtok(line, &delimiter);
        if (token) {
            array[*count] = strdup(token);
            (*count)++;
        }
    }

    fclose(file);
    return array;
}

Contact** generateContacts(char** firstNames, char** lastNames, int count) {
    Contact** contacts = malloc(count * sizeof(Contact*));

    for (int i = 0; i < count; i++) {
        contacts[i] = malloc(sizeof(Contact));
        contacts[i]->name = strdup(firstNames[i]);
        contacts[i]->last_name = strdup(lastNames[i]);
        // Dupliquer et convertir le prénom en minuscules
        contacts[i]->name = strdup(firstNames[i]);
        for (char* p = contacts[i]->name; *p; ++p) *p = tolower(*p);

        // Dupliquer et convertir le nom de famille en minuscules
        contacts[i]->last_name = strdup(lastNames[i]);
        for (char* p = contacts[i]->last_name; *p; ++p) *p = tolower(*p);

        contacts[i]->nbrMeeting = 0;
        contacts[i]->meetings = NULL;
    }

    return contacts;
}


void freeStringArray(char** array, int count) {
    for (int i = 0; i < count; i++) {
        free(array[i]);
    }
    free(array);
}

void freeLevelList(t_level_list* list) {
    if (list == NULL) {
        return; // Rien à libérer si la liste est nulle
    }

    // Commencez par libérer les cellules de chaque niveau
    for (int i = 0; i <= list->level; i++) {
        t_cell* current = list->heads->levels[i];
        while (current != NULL) {
            t_cell* next = current->levels[i];
            free(current);
            current = next;
        }
    }

    // Ensuite, libérez la mémoire de la structure de la liste et de la tête
    free(list->heads);
    free(list);
}


void createThousandContactList(t_level_list* list){
    int firstNameCount, lastNameCount;

    char** firstNames = readCsvFile("../1000_prenom.csv", &firstNameCount, ';');
    char** lastNames = readCsvFile("../fichier_fusionne.csv", &lastNameCount, ',');

    int totalContacts = firstNameCount < lastNameCount ? firstNameCount : lastNameCount;
    Contact** contacts = generateContacts(firstNames, lastNames, totalContacts);
    int i;
    for (i = 0; i < totalContacts; i++) {
        insertContact(list, contacts[i]);
        displayLoadingBar(i + 1, totalContacts); // Mise à jour de la barre de chargement
        usleep(500);
    }
    displayLoadingBar(i + 1, totalContacts); // Mise à jour de la barre de chargement


    // Libérer la mémoire
    freeStringArray(firstNames, firstNameCount);
    freeStringArray(lastNames, lastNameCount);
}
