#include "../include/FileManager.h"
#include "../include/Utils.h"


// checks and redirects if the backups exceed 5
void checkBackupFiles(void) {
    if (countBackupFiles("storage/backup") > MAX_BACKUPS){
        cleanupOldBackups();
    }
}


void cleanupOldBackups(void) {
    // rewrite this section of code basically this is what eneds to happen
    // look through all the files and comapre via the qsort in utilse and finds the oldest one
    // which then we delete
}

// Generates a unique backup filename with timestamp (e.g. backup_20250614_180000.dat)
static void generateBackupFileName(char *fileName, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestamp[32];

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

    char backupFileName[256];
    generateBackupFileName(backupFileName, sizeof(backupFileName));

    FILE *backupFile = fopen(backupFileName, "wb");
    if (backupFile == NULL) {
        printf("Error opening backup file: %s\n", backupFileName);
        fclose(file);
        return;
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, backupFile);
    }

    fclose(file);
    fclose(backupFile);
    printf("Backup created: %s\n", backupFileName);
}
