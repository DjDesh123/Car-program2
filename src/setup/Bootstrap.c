#include <stdio.h>

#include "setup/Bootstrap.h"
#include "inventory/Inventory.h"
#include "utils/FileManager.h"

// This file will be used to load the essential files into the program upon booting
void initSystemStorage() {

  // first need to check the file and folder exist
  if (checkInventoryFileExist()) {
    //call the loading function
    createInventory();
    return;
  }

  // checks if the storage directory  exists
  if (createStorageFolder() != 0){
    return;
  }

  // checks if the backup directory exists
  if (createBackupFolder() != 0) {
    return;
  }

  // this will load the inventory from the newest saved backup as long as the other two have happened because this wouldn't exist if they didn't
  if (!loadInventoryFromBackupFile()) {
    // checks if the json file exist which isn't hard just the file path
    // if exist then read or if it doesn't exist then create

  }

  //TODO:checks if the json file exists which if not its created with the default data and then we can move
  // if  it does exist then we need to load from the json to a struct array and boom it should all work
}

// creates the first main storage folder
static int createStorageFolder() {

  // checks if the file already exist
  if (directoryExists("storage")) {
    return 0;
  }

  // if MKDIR is 0 then the file opened properly
  if (MKDIR("storage") != 0) {
    perror("Failed to create the storage directory");
    return -1;
  }

  printf("creating folder....\n");
  return 0;
}

// creates the backup folder
static int createBackupFolder() {

  if (directoryExists("storage/backup")) {
    printf("backup directory already exist\n");
    return 0;
  }

  if (MKDIR("storage/backup") != 0) {
    perror("Failed to create the backup directory");
    return -1;
  }

  printf("creating folder....\n");

  return 0;
}
// this function does multiple things what I can do is create a sub function and just call that which then will also handle all the other function calls that are needed to amke it work
static bool checkInventoryFileExist() {
  // creates a pointer to the file and puts it in read binary mode for efficiency
  FILE *file = fopen("storage/Inventory.dat", "rb");

  // checks if the file exist
  if (file) {
    //The scenario the file exist
    printf("File already exists.\n");
    fclose(file);
    return true;
  }
  fclose(file);
  return false;
}



