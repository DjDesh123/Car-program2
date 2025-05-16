#include "../include/setup/Bootstrap.h"
#include "../include/setup/DefaultInventory.h"

#include <stdio.h>


// This file will be used to load the essential files into the program upon booting
void initSystemStorage() {
  // first need to check the file and folder exist
  checkInventoryFileExist();

}

// creates the first main storage folder
void createStorageFolder() {
  MKDIR("storage");
}

// creates the backup folder
void createBackupFolder() {
  MKDIR("storage/backup");
}

void checkInventoryFileExist() {
  FILE *file = fopen("storage/Inventory.txt", "r");

  if (file) {
    //The scenario the file exist
    printf("File already exists.\n");
    fclose(file);
  }else {
    // in the scenario the file doesnt exist
    createBackupFolder();
    createBackupFolder();
    defaultInventory();
  }
}