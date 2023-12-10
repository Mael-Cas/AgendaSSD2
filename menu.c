#include "menu.h"
#include "save.h"
#include <stdio.h>
#include "timer.h"
#include <math.h>
#include "partie1-2/list_value.h"
#include "graph/pbPlots.h"
#include "graph/supportLib.h"


int randomInRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

void TestTimer(int n, int numberOfSearch, int* opti, int* nopti) {
    t_level_list *list = createLevelList();
    int max_val = pow(2, n);
    max_val--;
    for (int lvl = 0; lvl < n; lvl++) {
        for (int val = 1; val < max_val + 1; val++) {
            int modulo = pow(2, (lvl + 1));
            if ((val % modulo)) {
                InsertValueLevelList(list, val, lvl);
            }
        }
    }
    int valToSearch;

    startTimer();
    for(int i = 0; i < numberOfSearch ; i++){
        valToSearch = randomInRange(1, 512);
        searchInValueList(list, valToSearch);
    }
    stopTimer();

    *opti = getTimeAsMsecs();
    startTimer();
    for(int i = 0; i < numberOfSearch ; i++){
        valToSearch = randomInRange(1, 512);
        classicSearchInValueList(list, valToSearch);
    }
    stopTimer();
    *nopti = getTimeAsMsecs();
}

void printMenu() {
    printf("\nMain Menu\n");
    printf("1. Search for a contact\n");
    printf("2. Display meetings for a contact\n");
    printf("3. Create a contact\n");
    printf("4. Create a meeting for a contact\n");
    printf("5. Delete a meeting\n");
    printf("6. Save all meetings to a file\n");
    printf("7. Load meetings from a file\n");
    printf("8. Display all contacts\n");
    printf("9. Display computation times for insertion\n");
    printf("10. Create a list with 1 000 contacts.\n");
    printf("11. Exit\n");
    printf("Please choose an option: ");
}

// Menu pour tester les parties 1 et 2
void printMenu1() {
    printf("\nMain Menu\n");
    printf("1. Search for a value\n");
    printf("2. Add a value\n");
    printf("3. Delete a value\n");
    printf("4. Display all values \n");
    printf("5. Display only one level\n");
    printf("6. Display computation times for insertion\n");
    printf("7. Exit\n");
    printf("Please choose an option: ");
}

// Execution des choix pour les parties 1 et 2
void executeOption1(t_level_list_value*list, int option){
    switch (option){
        case 1: {
            printf("Which value do you wonna search ? \n");
            int valueToSearch;
            while(scanf("%d", &valueToSearch) != 1){
                printf("Please, enter a int number : \n");
            }
            if(searchInValueList(list, valueToSearch)){
                printf("%d value is in the list.\n", valueToSearch);
            }else{
                printf("%d value is not in the list.\n", valueToSearch);
            }
            break;
        }
        case 2:{
            printf("Which value do you want to add ? \n");
            int valueToAdd;
            while(scanf("%d", &valueToAdd) != 1){
                printf("Please, enter a int number : \n");
            }
            printf("At which level do you want to add the value %d ? \n", valueToAdd);
            int levelToAdd;
            while(scanf("%d", &levelToAdd) != 1 && levelToAdd < 0 || levelToAdd > MAX_LEVEL_VALUE){
                printf("Please, enter a valid number (between %d and %d) : \n", 0, MAX_LEVEL_VALUE);
            }
            InsertValueLevelList(list, valueToAdd, levelToAdd);
            break;
        }
        case 3:{
            printf("Which value do you want to delete ? \n");
            int valueToDelete;
            while(scanf("%d", &valueToDelete) != 1){
                printf("Please, enter a int number : \n");
            }
            if(searchInValueList(list, valueToDelete)) {
                deleteValueNode(list, valueToDelete);
            }else{
                printf("%d doesn't exist in the list.\n", valueToDelete);
            }
            break;
        }
        case 4:{
            displayValueLevelList(list);
            break;
        }
        case 5:{
            printf("Which level do you want to display ? \n");
            int levelToDisplay;
            while(scanf("%d", &levelToDisplay) != 1 && levelToDisplay < 0 || levelToDisplay > MAX_LEVEL_VALUE){
                printf("Please, enter a valid number (int between %d and %d) : \n", 0, MAX_LEVEL_VALUE);
            }
            displayOneLevelValue(list, levelToDisplay);
            break;
        }
        case 6:{
            int OptimisedAlgo, NonOptimisedAlgo;
            /*
            // For a 1 000 research
            TestTimer(5, 1000, &OptimisedAlgo, &NonOptimisedAlgo);
            printf("For 1 000 : \n");
            printf("Time for level search : %d ms.\n", OptimisedAlgo);
            printf("Time for one search : %d ms.\n", NonOptimisedAlgo);
            // For a 100 000 research
            TestTimer(5, 100000, &OptimisedAlgo, &NonOptimisedAlgo);
            printf("For 100 000 : \n");
            printf("Time for level search : %d ms.\n", OptimisedAlgo);
            printf("Time for one search : %d ms.\n", NonOptimisedAlgo);
            // For a 1 000 000 research
            TestTimer(5, 1000000, &OptimisedAlgo, &NonOptimisedAlgo);
            printf("For 1 000 000 : \n");
            printf("Time for level search : %d ms.\n", OptimisedAlgo);
            printf("Time for one search : %d ms.\n", NonOptimisedAlgo);
             */

            double xs [30];
            double ys [30];

            double xs2 [30];
            double ys2 [30];


            srand(time(NULL));

            printf("How many level do you want to test ? \n");
            int numberoflevel, result;
            do{
                printf("Please enter a number between 0 and 15 :");
                result = scanf("%d", &numberoflevel);
            }while(result != 1 && (numberoflevel < 0 || numberoflevel > 15));

            int cpt = 0;
            for(int i = 0; i < numberoflevel ; i++){
                int op1, op2, op3;
                int nop1, nop2, nop3;
                TestTimer(i, 1000, &op1, &nop1);
                TestTimer(i, 100000, &op2, &nop2);
                TestTimer(i, 1000000, &op3, &nop3);

                xs[cpt] = i;
                ys[cpt] = (op1 + op2 + op3)/3;

                xs2[cpt] = i;
                ys2[cpt] = (nop1 + nop2 + nop3)/3;


                cpt += 1;

                displayLoadingBar(i, numberoflevel);
            }

            _Bool success;
            StringReference *errorMessage;

            StartArenaAllocator();

            RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();



            ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
            series->xs = xs;
            series->xsLength = cpt;
            series->ys = ys;
            series->ysLength = cpt;
            series->linearInterpolation = true;
            series->pointType = L"dashed";
            series->pointTypeLength = wcslen(series->pointType);
            series->lineThickness = 2;
            series->color = CreateRGBColor(1, 0, 0);

            ScatterPlotSeries *series2 = GetDefaultScatterPlotSeriesSettings();
            series2->xs = xs2;
            series2->xsLength = cpt;
            series2->ys = ys2;
            series2->ysLength = cpt;
            series2->linearInterpolation = true;
            series2->lineType = L"solid";
            series2->lineTypeLength = wcslen(series2->lineType);
            series2->lineThickness = 2;
            series2->color = CreateRGBColor(0, 0, 1);

            ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
            settings->width = 1920;
            settings->height = 1080;
            settings->autoBoundaries = true;
            settings->autoPadding = true;
            settings->title = L"Complexité de la recherche";
            settings->titleLength = wcslen(settings->title);
            settings->xLabel = L"niveau";
            settings->xLabelLength = wcslen(settings->xLabel);
            settings->yLabel = L"temps en ms";
            settings->yLabelLength = wcslen(settings->yLabel);
            ScatterPlotSeries *s [] = {series, series2};
            settings->scatterPlotSeries = s;
            settings->scatterPlotSeriesLength = 2;

            errorMessage = (StringReference *)malloc(sizeof(StringReference));
            success = DrawScatterPlotFromSettings(imageReference, settings, errorMessage);

            if(success){
                ByteArray *pngdata = ConvertToPNG(imageReference->image);
                WriteToFile(pngdata, "Complexite_level.png");
                DeleteImage(imageReference->image);
                printf("\n");
                printf("Succes ! The graph is on the file : \"Complexite_level.png\" \n");


            }else{
                fprintf(stderr, "Error: ");
                for(int i = 0; i < errorMessage->stringLength; i++){
                    fprintf(stderr, "%c", errorMessage->string[i]);
                }
                fprintf(stderr, "\n");
            }

            FreeAllocations();

            break;
        }
        case 7:
            printf("Good Bye !\n");
            break;
        default:
            printf("Invalid option. Try again !");
    }
}

void executeOption(t_level_list *list, int option) {
    switch (option) {
        case 1: {
            Contact* found = autocompleteSearch(list);
            clearInputBuffer();
            if (found) {
                printf("Contact found : ");
                printContact(found);
            } else {
                printf("Contact not found.\n");
            }
            break;
        }
        case 2: {
            Contact *found = autocompleteSearch(list);
            if (found) {
                displayMeetings(*found);
            } else {
                printf("No contacts found to display meetings.\n");
            }
            break;
        }
        case 3: {
            Contact *newContact = createContact();
            insertContact(list, newContact);
            printf("Contact created and inserted successfully.\n");
            break;
        }
        case 4: {
            Contact *found = autocompleteSearch(list);
            if (found) {
                addMeeting(found);
                printf("\nMeeting added.\n");
            } else {
                printf("Creating a new contact for the meeting.\n");
                Contact *newContact = createContact();
                addMeeting(newContact);
                insertContact(list, newContact);
            }
            break;
        }
        case 5: {
            Contact *found = autocompleteSearch(list);
            if (found) {
                deleteMeeting(found);
                printf("Meeting deleted.\n");
            } else {
                printf("No contacts found to delete a meeting.\n");
            }
            break;
        }
        case 6: {
            saveToFile(list, "../saving.txt");
            printf("The meetings are saved.\n");
            break;
        }
        case 7: {
            printf("Do you to load the 1 000 contact list ? (y/n)\n");
            char choice;
            do{
                scanf(" %c", &choice);
            }while(choice != 'y' && choice != 'n');
            clearInputBuffer();
            if(choice == 'y'){
                createThousandContactList(list);
                saveToFile(list, "../1000_Contacts.txt");
                printf("File 1000_Contacts.txt created and loaded.\n");
            }else{
                loadFromFile(list, "../saving.txt");
            }
            printf("Meetings are reloaded.\n");
            break;
        }
        case 8:
            displayLevelList(list);
            break;
        case 9: {
            // Mesurer le temps de l'application
            break;
        }
        case 10:
            createThousandContactList(list);
            saveToFile(list, "../1000_Contacts.txt");
            printf("File 1000_Contacts.txt created.\n");
            break;
        case 11:
            printf("Good Bye !\n");
            break;
        default:
            printf("Invalid option. Try Again.\n");
    }
}

