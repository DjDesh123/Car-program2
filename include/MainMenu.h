#ifndef MAINMENU_H
#define MAINMENU_H

// function prototype
void mainMenu();

// to improve readability we used enums
typedef enum {VIEW_CARS = 1,BUY_CAR=2,VIEW_STATS=3,SELL_CAR=4,EXIT=5} menuOption;


extern int menuChoice;

#endif //MAINMENU_H
