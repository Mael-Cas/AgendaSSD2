/*
    Projet TI301 - Algorithmique et structures de données
    Par : Maël CASTELLAN - Doryan DENIS - Rémi DESJARDINS
    L2 - GROUPE A - EFREI PARIS
    timer.h/.c : Contient les fonctions de chronométrage pour l'étude de la complexité
*/

#ifndef AGENDASSD2_TIMER_H
#define AGENDASSD2_TIMER_H

#include <time.h>
// timer structure
typedef struct s_timer
{
    clock_t _start; // start time
    clock_t _end;   // end time
    double _msecs;  // duration in milliseconds
} t_timer;

static t_timer _timer;

/**
 * @brief start the timer
 * @param none
 * @return none
 */
void startTimer();

/**
 * @brief stop the timer
 * @param none
 * @return none
 */
void stopTimer();

/**
 * @brief display the time
 * @param none
 * @return none
 */
void displayTime();

/**
 * @brief return a string with the time in seconds and milliseconds
 * @param none
 * @return a string with the time in seconds and milliseconds
 */
char *getTimeAsString();

int getTimeAsMsecs();




#endif //AGENDASSD2_TIMER_H
