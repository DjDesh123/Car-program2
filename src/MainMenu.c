#include "MainMenu.h"
#include "Utils.h"

static void showDisplay();

// to improve readability we used enums
typedef enum {VIEW_CARS = 1,BUY_CAR=2,VIEW_STATS=3,SELL_CAR=4,EXIT=5} menuOption;

void mainMenu() {
    int menuChoice;

    // Displays the options that the user can pick
    showDisplay();

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

static void showDisplay() {
    printf("---- Car Dealership System ----\n");
    printf("1. View Available Cars\n");
    printf("2. Buy Cars\n");
    printf("3. View Sales Stats\n");
    printf("4. Sell Car\n");
    printf("5. Exit\n");
}