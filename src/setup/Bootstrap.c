#include "Bootstrap.h"
#include "Inventory.h"
#include "FileManager.h"


static void checkStorageDirectoriesExist();
static void recoverCarData();


// This file will be used to load the essential files into the program upon booting
void initSystemStorage() {
  
  // first check if the directories even exist
  //if not they will be created
  checkStorageDirectoriesExist();

  // if the file does not exist then we go down the process
  if (!checkInventoryFileExist()) {
    // continue with checks if not then go through the process of loading backups then json etc etc
    recoverCarData();
    return;
  }


  //TODO:checks if the json file exists which if not its created with the default data and then we can move
  // if  it does exist then we need to load from the json to a struct array and boom it should all work
}



static void recoverCarData(){
  // load the inventory from the newest saved backup as long as the other two have happened because this wouldn't exist if they didn't
  if (!loadInventoryFromBackupFile()) {
    // we first now neeed to check if we can load the backups
    findRecentBackup();

  }
  
}
static void checkStorageDirectoriesExist(){
  // checks if the storage directory  exists
  if (createStorageFolder() == true){
    return;
  }

  // checks if the backup directory exists
  if (createBackupFolder() == true) {
    return;
  }


}



