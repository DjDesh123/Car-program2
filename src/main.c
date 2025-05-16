#include "../include/MainMenu.h"
#include "../include/setup/Bootstrap.h"


int main(void){
  // calls the bootstrap and the main menu
  initSystemStorage();
  mainMenu();
  return 0;
}