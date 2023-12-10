//
// Created by Rémi Desjardins on 30/11/2023.
//

#ifndef AGENDASSD2_MEETING_H
#define AGENDASSD2_MEETING_H



typedef struct date{
    int day;
    int month;
    int year;
}Date;

typedef struct time{
    int hour;
    int minute;
}Time;

// Structure pour représenter un rendez-vous
typedef struct meeting {
    Date time; // Date du rendez-vous
    Time StartTime; // Heure de début
    Time EndTime; // Heure de fin
    char *objet; // Objet du rendez-vous
    int id; // Identifiant unique
    struct meeting *next; // Pointeur vers le prochain rendez-vous
} Meeting;

// Structure pour représenter un contact
typedef struct contact {
    char *name; // Prénom du contact
    char *last_name; // Nom de famille du contact
    int nbrMeeting; // Nombre de rendez-vous associés
    Meeting *meetings; // Liste des rendez-vous du contact
} Contact;


// Structure pour représenter un calendrier de rendez-vous
typedef struct s_Calendar {
    Meeting *head; // Pointeur vers le premier rendez-vous
} t_Calendar;

// Fonctions pour les saisies sécurisées
int isValidTime(Time time);
int isValidDate(Date data);
int isValidDate(Date date);

// Fonctions pour faire saisir les données
int scanTime(Time *, const char *);
int scanDate(Date*);
int scanTime(Time*, const char*);
char *scanString(void);
char scanChar();


// Fonctions pour les rendez-vous
Meeting *createMeeting(int);
void addMeeting(Contact *contact);
void deleteMeeting(Contact *);
void modifyMeeting(Contact *);
int isEmptyMeeting(Contact);
void displayMeetings(Contact);

// Fonctions pour les contacts
Contact *createContact();
void displayContact(Contact contact);
int compareContact(const Contact*, const Contact*);
void printContact(Contact*);


void clearInputBuffer();

#endif //AGENDASSD2_MEETING_H
