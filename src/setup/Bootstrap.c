#include "../include/setup/Bootstrap.h"
#include "../include/setup/DefaultInventory.h"
#include "../include/FileManager.h"



// This file will be used to load the essential files into the program upon booting
void initSystemStorage() {
  // first need to check the file and folder exist
  checkInventoryFileExist();

}

// creates the first main storage folder
void createStorageFolder() {
  if (!directoryExists("storage")) {
    printf("storage directory does not exist\n");
    printf("creating folder....\n");
    MKDIR("storage");
  }
}

// creates the backup folder
void createBackupFolder() {
  if (!directoryExists("storage/backup")) {
    printf("backup directory does not exist\n");
    printf("creating folder....\n");
    MKDIR("storage/backup");
  }
}

void checkInventoryFileExist() {
  FILE *file = fopen("storage/Inventory.dat", "r");

  if (file) {
    //The scenario the file exist
    printf("File already exists.\n");
    fclose(file);

  }else {
    // first we need to load a backup if present then if it doesnt exist or the file corrupted
    //then need to create the json file as the last wall of defence

    // checks and or creates the storage or backup folders
    createStorageFolder();
    createBackupFolder();

    // to initialise and write the Inventory.dat in the correct folder
    defaultInventory();

    // in the scenario that the file does not exist then a backup will be created
    backupFile("./storage/Inventory.dat","./storage/backup/backup.dat");
  }
}

bool directoryExists(const char *path) {
  struct STAT st;

  // Check if the given path exists and is a directory:
  // 1. Use stat() to get info about the path; returns 0 if successful.
  // 2. Check the file mode bits to see if it's flagged as a directory.
  // Returns true if both conditions are met, false otherwise.
  return (STAT(path, &st) == 0 && (st.st_mode & S_IFDIR));
}
