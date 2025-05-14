#include "../include/setup/Bootstrap.h"


// This file will be used to load the essential files into the program upon booting
void initSystemStorage() {
  createStorageFolder();
  createBackupFolder();

}

// creates the first main storage folder
void createStorageFolder() {
  MKDIR("storage");
}

// creates the backup folder
void createBackupFolder() {
  MKDIR("storage/backup");

}