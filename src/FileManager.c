#include "FileManager.h"

#include <Inventory.h>
#include <stdbool.h>

#include "Utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 1024
#define TIMESTAMP_MAX 32
#define CHARACTER_MAX 256

#define BACKUP_PREFIX "backup_"
#define BACKUP_EXT ".dat"

#define BACKUP_DIR "./storage/backup"

#ifdef _WIN32
    #define MKDIR(path) _mkdir(path)
    #define PATH_SEP '\\'
#else
    #include <dirent.h>
    #include <sys/stat.h>
    #include <unistd.h>

    #define MKDIR(path) mkdir(path, 0777)
    #define PATH_SEP '/'
#endif



// checks and redirects if the backups exceed 5
void checkBackupFiles(void) {
    if (countBackupFiles("storage/backup") > MAX_BACKUPS){
        cleanupOldBackups();
    }
}


void cleanupOldBackups(void) {

    size_t count = countBackupFiles("storage/backup");

    if (count < MAX_BACKUPS) {
        return;
    }

    char **files = createFileNameArray(count,BACKUP_DIR);

    if (!files) {
        return;
    }

    // sorts backups from oldest to newest
    qsort(files,count,sizeof(char *),compareBackupTime);


    char fullPath[CHARACTER_MAX];

    // Build full path safely using a fixed-size buffer.
    // snprintf is used to prevent buffer overflows when filenames are longer than expected.
    snprintf(fullPath,sizeof(fullPath),"%s%c%s",BACKUP_DIR,PATH_SEP,BACKUP_DIR,files[0]);

    removeBackupFile(fullPath);

    // frees all the pointers from the char**
    for (size_t i = 0; i < count; i++) {
        free(files[i]);
    }
}

// Generates a unique backup filename with timestamp (e.g. backup_20250614_180000.dat)
static void generateBackupFileName(char *fileName, const int size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestamp[TIMESTAMP_MAX];

    // formats the timestamp
    strftime(timestamp, size, "%Y%m%d_%H%M%S.dat", t);

    // composes full backup filename with using the macros for path and naming
    snprintf(fileName,sizeof(timestamp),"%s%c%s%s%s",BACKUP_DIR,PATH_SEP,BACKUP_PREFIX,timestamp,BACKUP_EXT);
}

// Full flow to create a backup of a file and clean old ones first
void backupFile(const char* fileName) {
// this needs to be the check first which can be in a seperate function and can be called

    cleanupOldBackups(); // Always clean before adding a new one

    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        perror("Error opening source file");
        return;
    }

    char backupFileName[CHARACTER_MAX];
    generateBackupFileName(backupFileName, sizeof(backupFileName));

    FILE *backupFile = fopen(backupFileName, "wb");
    if (backupFile == NULL) {
        printf("Error opening backup file: %s\n", *compareBackupTime);
        fclose(file);
        return;
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, backupFile);
    }

    fclose(file);
    fclose(backupFile);
    printf("Backup created: %s\n", backupFileName);
}

void removeBackupFile(const char* fileName) {
    if (remove(fileName) != 0) {
        perror("remove failed");
    }
}

int loadInventoryFromBackupFile() {
    const size_t count = countBackupFiles("storage/backup");

    if (count < MAX_BACKUPS) {
        return false;
    }

    char **files = createFileNameArray(count,BACKUP_DIR);

    if (!files) {
        perror("Error opening backup files");
        return false;
    }

    // sorts backups from oldest to newest
    qsort(files,count,sizeof(char *),compareBackupTime);


    char fullPath[CHARACTER_MAX];

    // Build full path safely using a fixed-size buffer.
    // snprintf is used to prevent buffer overflows when filenames are longer than expected.
    snprintf(fullPath,sizeof(fullPath),"%s%c%s",BACKUP_DIR,PATH_SEP,files[count-1]);

    // frees all the pointers from the char**
    for (size_t i = 0; i < count; i++) {
        free(files[i]);
    }

    long fileSize = getFileSize(fullPath);
    long inventorySize = fileSize/sizeof(car);


    car *carInventory = malloc(inventorySize*sizeof(car));
    FILE *inventoryFile = fopen(fullPath, "rb");

    if (inventoryFile == NULL) {
        perror("Error opening backup file");
    }

    size_t inventoryItems =fread(carInventory,sizeof(car),inventorySize,inventoryFile);

    fclose(inventoryFile);


}



/* gets the newest backup from the array and then just turns it into local storage
int loadInventoryFromBackup() {
    char fileNamesArr[] =

}
*/
