#include "../include/FileManager.h"

#include <time.h>


// Handles file-related operations such as creating backups.
// This can be called from the bootloader or other parts of the program.

void backupFile(const char* fileName) {

    // Open the source file in binary read mode
    FILE *file = fopen(fileName, "rb");

    if (file == NULL) {
        perror("Error opening source file.\n");
        return;
    }

    // creates the backup file name
    char backupFileName[256];
    generateBackupFileName(backupFileName, sizeof(backupFileName));

    // Create the backup file in binary write mode
    FILE *backupFile = fopen(backupFileName, "wb");

    if (backupFile == NULL) {
        printf("Error opening backup file %s\n", backupFileName);
        return;
    }

    char buffer[1024];
    size_t bytesRead = 0;

    // Read source file in chunks and write to backup
    while ((bytesRead = fread(buffer, sizeof(char), 1024, file))) {
        fwrite(buffer, sizeof(char), bytesRead, backupFile);
    }

    fclose(file);
    fclose(backupFile);

}

// generates the file anme
static void generateBackupFileName(const char* fileName,size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(fileName, size, "./storage/backup/backup_%Y%m%d_%H%M%S.dat", t);
}