#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ANSI color codes
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define CYAN    "\033[1;36m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define RESET   "\033[0m"

// Structure for each routine entry
typedef struct RoutineEntry {
    char day[10];
    char subject[50];
    char time[10];
    struct RoutineEntry* next;
} RoutineEntry;

// Linked List manager
typedef struct {
    RoutineEntry* head;
} RoutineList;

// Initializes a routine list
void initializeRoutineList(RoutineList* list) {
    list->head = NULL;
}

// ✅ Adds a new entry (no overlaps allowed)
void addEntry(RoutineList* list, char* day, char* subject, char* time) {
    RoutineEntry* temp = list->head;
    while (temp != NULL) {
        if (strcmp(temp->day, day) == 0 && strcmp(temp->time, time) == 0) {
            printf(RED "Error: An entry already exists for %s at %s.\n" RESET, day, time);
            return;
        }
        temp = temp->next;
    }

    RoutineEntry* newEntry = (RoutineEntry*)malloc(sizeof(RoutineEntry));
    strcpy(newEntry->day, day);
    strcpy(newEntry->subject, subject);
    strcpy(newEntry->time, time);
    newEntry->next = list->head;
    list->head = newEntry;

    printf(GREEN "Entry added successfully!\n" RESET);
}

// Deletes an entry
void deleteEntry(RoutineList* list, char* day, char* subject) {
    RoutineEntry* temp = list->head;
    RoutineEntry* prev = NULL;

    while (temp != NULL && (strcmp(temp->day, day) != 0 || strcmp(temp->subject, subject) != 0)) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf(RED "Entry not found.\n" RESET);
        return;
    }

    if (prev == NULL) {
        list->head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf(GREEN "Entry deleted successfully.\n" RESET);
}

// Changes an existing entry (with overlap check)
void changeEntry(RoutineList* list, char* day, char* subject, char* newDay, char* newSubject, char* newTime) {
    RoutineEntry* temp = list->head;

    while (temp != NULL && (strcmp(temp->day, day) != 0 || strcmp(temp->subject, subject) != 0)) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf(RED "Entry not found.\n" RESET);
        return;
    }

    // Overlap check
    RoutineEntry* check = list->head;
    while (check != NULL) {
        if (check != temp && strcmp(check->day, newDay) == 0 && strcmp(check->time, newTime) == 0) {
            printf(RED "Error: An entry already exists for %s at %s.\n" RESET, newDay, newTime);
            return;
        }
        check = check->next;
    }

    strcpy(temp->day, newDay);
    strcpy(temp->subject, newSubject);
    strcpy(temp->time, newTime);
    printf(GREEN "Entry updated successfully.\n" RESET);
}

// Print routine entries
void printRoutine(RoutineList* list) {
    RoutineEntry* temp = list->head;

    if (temp == NULL) {
        printf(YELLOW "No routine entries found.\n" RESET);
        return;
    }

    printf("\n----------------------------------------------------------\n");
    printf("                 CLASS ROUTINE SCHEDULE                  \n");
    printf("----------------------------------------------------------\n");
    printf("| %-10s | %-20s | %-10s |\n", "Day", "Subject", "Time");
    printf("----------------------------------------------------------\n");

    while (temp != NULL) {
        printf("| %-10s | %-20s | %-10s |\n", temp->day, temp->subject, temp->time);
        temp = temp->next;
    }

    printf("----------------------------------------------------------\n");
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    RoutineList routine;
    initializeRoutineList(&routine);

    int choice;
    char day[10], subject[50], time[10], newDay[10], newSubject[50], newTime[10];

    while (1) {
        clearScreen();
        printf(BLUE "\n================== CLASS ROUTINE MANAGER ==================\n" RESET);
        printf("1. Add Entry\n");
        printf("2. Delete Entry\n");
        printf("3. Change Entry\n");
        printf("4. Print Routine\n");
        printf("5. Exit\n");
        printf("===========================================================\n");
        printf(YELLOW "Enter your choice: " RESET);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter day: "); scanf("%s", day);
                printf("Enter subject: "); scanf("%s", subject);
                printf("Enter time: "); scanf("%s", time);
                addEntry(&routine, day, subject, time);
                break;

            case 2:
                printf("Enter day: "); scanf("%s", day);
                printf("Enter subject: "); scanf("%s", subject);
                deleteEntry(&routine, day, subject);
                break;

            case 3:
                printf("Enter current day: "); scanf("%s", day);
                printf("Enter current subject: "); scanf("%s", subject);
                printf("Enter new day: "); scanf("%s", newDay);
                printf("Enter new subject: "); scanf("%s", newSubject);
                printf("Enter new time: "); scanf("%s", newTime);
                changeEntry(&routine, day, subject, newDay, newSubject, newTime);
                break;

            case 4:
                printRoutine(&routine);
                break;

            case 5:
                printf(GREEN "\nExiting... Have a great day!\n" RESET);
                exit(0);

            default:
                printf(RED "Invalid choice. Please try again.\n" RESET);
        }

        printf(YELLOW "\nPress Enter to continue..." RESET);
        getchar(); getchar(); // Wait for Enter
    }

    return 0;
}
