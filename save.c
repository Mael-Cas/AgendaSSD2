//
// Created by maelc on 03/12/2023.
//

#include "save.h"
#include <ctype.h>
#include <string.h>


void saveToFile(t_level_list* list, const char* filename){
    FILE* file = fopen(filename, "w");
    if(file == NULL){
        printf("Error opening file.\n");
        return;
    }
    t_cell* current = list->heads->levels[0];
    while(current != NULL){
        Contact* contact = current->contact;
        Meeting* meetings = contact->meetings;

        if(meetings != NULL){
            // Écrire chaque rendez-vous pour ce contact
            while(meetings != NULL){
                fprintf(file, "%s,%s,%d/%d/%d,%d:%d,%d:%d,%s\n",
                        contact->last_name, contact->name, meetings->time.day, meetings->time.month, meetings->time.year,
                        meetings->StartTime.hour, meetings->StartTime.minute,
                        meetings->EndTime.hour, meetings->EndTime.minute,
                        meetings->objet);
                meetings = meetings->next;
            }
        } else {
            // Écrire les informations du contact avec des valeurs par défaut ou des indicateurs pour les rendez-vous
            fprintf(file, "%s,%s,,,,,,,\n", contact->last_name, contact->name);
        }

        current = current->levels[0];
    }
    fclose(file);
}



void loadFromFile(t_level_list *list, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file.\n,");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char last_name[50], name[50], objet[100];
        int day, month, year, StartTime_hour, StartTime_minute, EndTime_hour, EndTIme_minute;

        if (sscanf(line, "%49[^,],%49[^,],%d/%d/%d,%d:%d,%d:%d,%99[^\n]",
                   last_name, name, &day, &month, &year, &StartTime_hour, &StartTime_minute, &EndTime_hour, &EndTIme_minute, objet) == 10) {
            // Création du contact et du rendez-vous
            Contact *newContact = (Contact *)malloc(sizeof(Contact));
            Meeting *newMeeting = (Meeting *)malloc(sizeof(Meeting ));

            newContact->name = strdup(name);
            newContact->last_name = strdup(last_name);
            newContact->meetings = newMeeting;

            newMeeting->time.day = day;
            newMeeting->time.month = month;
            newMeeting->time.year = year;
            newMeeting->StartTime.hour = StartTime_hour;
            newMeeting->StartTime.minute = StartTime_minute;
            newMeeting->EndTime.hour = EndTime_hour;
            newMeeting->EndTime.minute = EndTIme_minute;
            newMeeting->objet = strdup(objet);
            newMeeting->next = NULL;

            // Insérer le nouveau contact dans la liste
            insertContact(list, newContact);
        } else {
            fprintf(stderr, "Malformed or incomplete line: %s", line);
        }
    }

    fclose(file);
}


