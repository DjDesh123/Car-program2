#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H


// max files that can be held at a time
#define MAX_BACKUPS 5

// creates backup files
void backupFile(const char *fileName);

// removes old backups if needed
void cleanupOldBackups(void);

// deletes old backups
void removeBackupFile(const char *fileName);

// takes the newest backup fiel and laods it
int loadInventoryFromBackupFile();

#endif
