#include "../include/FileManager.h"

// Internal struct for tracking each backup's full path and last modified time
typedef struct {
    char path[256];            // Full path to backup file
    time_t modified_time;      // File's last modified time from system metadata
} BackupFile;

// Used for qsort() to sort backup files by last modified time (oldest first)
static int compareBackupTime(const void *a, const void *b) {
    const BackupFile *fileA = a;
    const BackupFile *fileB = b;
    return (fileA->modified_time < fileB->modified_time) ? -1 : 1;
}

// Main backup cleanup logic — deletes oldest .dat backups if we’ve reached the cap
void cleanupOldBackups(void) {

    WIN32_FIND_DATA findFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    char searchPath[512];

    DIR *dir = opendir(BACKUP_DIR);
    if (!dir) {
        perror("Failed to open backup directory");
        return;
    }

    BackupFile backups[100];
    size_t count = 0;
    struct dirent *entry;

    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && count < 100) {
            snprintf(backups[count].path, sizeof(backups[count].path), "%s\\%s", BACKUP_DIR, findFileData.cFileName);

            FILETIME ft = findFileData.ftLastWriteTime;
            ULARGE_INTEGER ull;
            ull.LowPart = ft.dwLowDateTime;
            ull.HighPart = ft.dwHighDateTime;
            backups[count].modified_time = (time_t)((ull.QuadPart / 10000000ULL) - 11644473600ULL);
            count++;
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    FindClose(hFind);

    if (count >= MAX_BACKUPS) {
        qsort(backups, count, sizeof(BackupFile), compareBackupTime);
        size_t toDelete = count - MAX_BACKUPS;

        for (size_t i = 0; i < toDelete; i++) {
            if (remove(backups[i].path) == 0) {
                printf("Deleted old backup: %s\n", backups[i].path);
            } else {
                perror("Failed to delete backup");
            }
        }
    }
}

// Generates a unique backup filename with timestamp (e.g. backup_20250614_180000.dat)
static void generateBackupFileName(char *fileName, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(fileName, size, "./storage/backup/backup_%Y%m%d_%H%M%S.dat", t);
}

// Full flow to create a backup of a file and clean old ones first
void backupFile(const char* fileName) {
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
