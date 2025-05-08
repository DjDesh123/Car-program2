#include <stdio.h>
#include "MainMenu.h"

#include <stdlib.h>


void mainMenu() {
    int menuChoice;

    // Displays the options that the user can pick
    printf("---- Car Dealership System ----\n");
    printf("1. View Available Cars\n");
    printf("2. Buy Cars\n");
    printf("3. View Sales Stats\n");
    printf("4. Sell Car\n");
    printf("5. Exit\n");
    printf("Select an option: ");
    scanf("%d", &menuChoice);

    // to loop untill the user enters a valid choice
    do {
        switch (menuChoice) {
            case VIEW_CARS:
                printf("Available Cars:\n");
            case BUY_CAR:
                printf("Buy Cars:\n");
            case VIEW_STATS:
                printf("View Sales Stats:\n");
            case SELL_CAR:
                printf("Sell Car:\n");
            case EXIT:
                exit(0);
            default:
                printf("Invalid Input\n");
        }
    }while(menuChoice<VIEW_CARS||menuChoice >EXIT);
}

