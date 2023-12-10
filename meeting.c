//
// Created by Rémi Desjardins on 30/11/2023.
//



#include "meeting.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>




char *scanString(){
    char buffer[100];
    if(fgets(buffer, sizeof(buffer), stdin) == NULL){
        return NULL; // Une erreur
    }
    size_t length = strlen(buffer);

    for(int i = 0; i < length ; i++){
        buffer[i] = tolower(buffer[i]);
    }

    if(length > 0 && buffer[length - 1] == '\n'){
        buffer[length - 1] = '\0';
        length--;
    }

    char* string = (char*)malloc(length+1);
    if(string == NULL)
        return NULL;
    strcpy(string, buffer);


    return string;
}

char scanChar() {
    char c;
    c = getchar();
    if (c == '\n' || c == EOF) {
        return '\0';
    }
    return tolower(c);
}


int isValidDate(Date date) {
    return date.day > 0 && date.day <= 31 && date.month > 0 && date.month <= 12 && date.year >= 1900;
}

int isValidTime(Time time) {
    return time.hour >= 0 && time.hour < 24 && time.minute >= 0 && time.minute < 60;
}

void clearInputBuffer() {
    fflush(stdin); // Vide le buffer d'entrée
    return;
}

int scanDate(Date *date) {
    while (1) {
        printf("Meeting date (dd mm yyyy): ");
        int result = scanf("%d %d %d", &date->day, &date->month, &date->year);
        clearInputBuffer();
        if (result == 3 && isValidDate(*date)) {
            break; // Sortir de la boucle si la date est valide
        } else {
            printf("Invalid date format or invalid date. Please try again.\n");
        }
    }
    return 1;
}


int scanTime(Time *time, const char *timePrompt) {
    int isValid = 0;
    while (!isValid) {
        printf("%s (hh mm): ", timePrompt);
        int result = scanf("%d %d", &time->hour, &time->minute);
        clearInputBuffer(); // Nettoyez toujours le buffer d'entrée après scanf

        if (result == 2 && isValidTime(*time)) {
            isValid = 1; // Sortir de la boucle si l'heure est valide
        } else {
            printf("Invalid time format or invalid time. Please try again.\n");
        }
    }
    return isValid; // Retourne 1 si l'heure a été saisie correctement
}


Meeting *createMeeting(int nbr) {
    Meeting *NewMeeting = (Meeting *)malloc(sizeof(Meeting));

    Date meetingDate;
    if (scanDate(&meetingDate)) {
        NewMeeting->time = meetingDate;
        scanTime(&NewMeeting->StartTime, "Start time");
        do {
            scanTime(&NewMeeting->EndTime, "End time");
            if (NewMeeting->StartTime.hour > NewMeeting->EndTime.hour ||
                (NewMeeting->StartTime.hour == NewMeeting->EndTime.hour &&
                 NewMeeting->StartTime.minute >= NewMeeting->EndTime.minute)) {
                printf("End time must be later than start time. Please enter the end time again.\n");
            }
        } while (NewMeeting->StartTime.hour > NewMeeting->EndTime.hour ||
                 (NewMeeting->StartTime.hour == NewMeeting->EndTime.hour &&
                  NewMeeting->StartTime.minute >= NewMeeting->EndTime.minute));
        fflush(stdin);
        printf("Purpose of the meeting :");
        NewMeeting->objet = scanString();
        NewMeeting->next = NULL;
        NewMeeting->id = nbr;
    }
    return NewMeeting;
}



int compareContact(const Contact* a, const Contact* b){
    int cmp = strcmp(a->last_name, b->last_name);
    if(cmp == 0)
        return strcmp(a->name, b->name);
    return cmp;
}

void scanContact(Contact* contact){

    fflush(stdin);
    printf("Name : \n");
    contact->name = scanString();
    printf("Last Name :   \n");
    contact->last_name = scanString();

}

Contact *createContact(){
    Contact *contact = (Contact *)malloc(sizeof(Contact));
    scanContact(contact);
    contact->nbrMeeting = 0;
    printf("Do you want create a new meeting ?(y/n)\n");
    char response = 'n';

    do{
        scanf(" %c", &response);
    }while(response != 'n' && response != 'y');



    if(response && response == 'y'){
        contact->nbrMeeting += 1;
        contact->meetings = createMeeting(contact->nbrMeeting);
    }else{
        contact->meetings = NULL;
    }

    return contact;
}

void printContact(Contact *contact){
    printf("%s_%s", contact->last_name, contact->name);
}


void addMeeting(Contact *contact){
    contact->nbrMeeting += 1;
    Meeting *newMeeting = createMeeting(contact->nbrMeeting);

    newMeeting->next = contact->meetings;
    contact->meetings = newMeeting;

}

void displayContact(Contact contact){
    while (getchar() != '\n');
    printf("Contact Information \n");
    printf("Name : %s\n", contact.name);
    printf("Last name : %s\n", contact.last_name);

    displayMeetings(contact);

}

void deleteMeeting(Contact *contact){
    displayMeetings(*contact);

    printf("Which meeting do you want delete ? Please enter the Id's meeting : ");
    int id;
    scanf("%d", &id);

    Meeting *currentMeeting = contact->meetings;
    Meeting *previewMeeting = NULL;

    while(currentMeeting->next != NULL){

        if(currentMeeting->id == id){

            if(previewMeeting == NULL){


                contact->meetings = currentMeeting->next;
                currentMeeting->next = NULL;
                free(currentMeeting);
                return;

            }else{

                previewMeeting->next = currentMeeting->next;
                currentMeeting->next = NULL;
                free(currentMeeting);
                return;

            }

        }

        previewMeeting = currentMeeting;
        currentMeeting = currentMeeting->next;

    }


    return;

};

void displayMeetings(Contact contact) {

    if(contact.meetings == NULL){
        printf("Any meeting for this contact.");
        return;
    }


    Meeting *currentMeeting = contact.meetings;
    printf("\nMeetings of %s %s :\n", contact.last_name, contact.name);
    while(currentMeeting != NULL){

        printf("Id : %d\n", currentMeeting->id);
        printf("Date: %02d/%02d/%04d\n", currentMeeting->time.day, currentMeeting->time.month, currentMeeting->time.year);
        printf("Start Time: %02d:%02d\n", currentMeeting->StartTime.hour, currentMeeting->StartTime.minute);
        printf("End Time: %02d:%02d\n", currentMeeting->EndTime.hour, currentMeeting->EndTime.minute);
        printf("Object: %s\n", currentMeeting->objet);


        currentMeeting = currentMeeting->next;
        printf("\n");
    }
}

void displayOneMeeting(Contact contact, int id){
    Meeting *currentMeeting = contact.meetings;

    while(currentMeeting != NULL){
        if(id == currentMeeting->id){
            printf("Id : %d\n", currentMeeting->id);
            printf("Date: %02d/%02d/%04d\n", currentMeeting->time.day, currentMeeting->time.month, currentMeeting->time.year);
            printf("Start Time: %02d:%02d\n", currentMeeting->StartTime.hour, currentMeeting->StartTime.minute);
            printf("End Time: %02d:%02d\n", currentMeeting->EndTime.hour, currentMeeting->EndTime.minute);
            printf("Object: %s\n", currentMeeting->objet);


            currentMeeting = currentMeeting->next;
            printf("\n");
        }
    }
}

int isEmptyMeeting(Contact contact){
    if(contact.meetings == NULL){
        return 1;
    }
    return 0;
}

void modifyMeeting(Contact *contact) {
    displayMeetings(*contact);

    if (isEmptyMeeting(*contact)) {
        printf("No meeting for this contact.\n");
        return;
    }

    int choice;
    printf("Which meeting do you want to modify? Please enter the meeting ID: ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input. Please enter a number.\n");
        clearInputBuffer(); // Clean the input buffer
        return;
    }
    clearInputBuffer(); // Clean the input buffer

    Meeting *modifyMeeting = contact->meetings;

    while (modifyMeeting != NULL) {
        if (modifyMeeting->id == choice) {
            printf("Enter the new date for the meeting:\n");
            Date newDate;
            if (scanDate(&newDate)) {
                modifyMeeting->time = newDate;
            } else {
                printf("Failed to update the meeting date.\n");
                return;
            }

            printf("Enter the new start time for the meeting:\n");
            Time newStartTime;
            if (scanTime(&newStartTime, "Start time")) {
                modifyMeeting->StartTime = newStartTime;
            } else {
                printf("Failed to update the start time.\n");
                return;
            }

            printf("Enter the new end time for the meeting:\n");
            Time newEndTime;
            if (scanTime(&newEndTime, "End time")) {
                modifyMeeting->EndTime = newEndTime;
            } else {
                printf("Failed to update the end time.\n");
                return;
            }

            printf("Enter the new purpose of the meeting: ");
            char *newPurpose = scanString();
            if (newPurpose) {
                free(modifyMeeting->objet); // Free the old string if it exists
                modifyMeeting->objet = newPurpose;
            } else {
                printf("Failed to update the purpose of the meeting.\n");
                return;
            }
            printf("Meeting updated successfully.\n");
            return;
        }
        modifyMeeting = modifyMeeting->next;
    }

    printf("Meeting ID not found.\n");
}

