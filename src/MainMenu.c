#include <stdio.h>
#include "../include/MainMenu.h"
#include "utils/Utils.h"

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


    // to loop until the user enters a valid choice
    do {
        printf("Select an option: ");
        scanf("%d", &menuChoice);
        switch (menuChoice) {
            case VIEW_CARS:
                printf("Available Cars:\n");
                break;
            case BUY_CAR:
                printf("Buy Cars:\n");
                break;
            case VIEW_STATS:
                printf("View Sales Stats:\n");
                break;
            case SELL_CAR:
                printf("Sell Car:\n");
                break;
            case EXIT:
                exit(0);
            default:
                printf("Invalid Input\n");
                clearInputBuffer();
                break;
        }
    }while(menuChoice<VIEW_CARS||menuChoice >EXIT);
}

