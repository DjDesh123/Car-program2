#include "../include/FileManager.h"




// Handles file-related operations such as creating backups.
// This can be called from the bootloader or other parts of the program.

void backupFile(const char* fileName, const char* backupFileName) {

    // Open the source file in binary read mode
    FILE *file = fopen(fileName, "rb");

    if (file == NULL) {
        perror("Error opening source file.\n");
    }

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
