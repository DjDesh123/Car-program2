#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <stdbool.h>

//TODO: fix this as well
// for windows
#ifdef _WIN32
    #include <direct.h>
    #include <sys/stat.h>
    #define STAT _stat
    #define S_IFDIR _S_IFDIR
    #define MKDIR(path) _mkdir(path)
// for linux and apple
#else
    #define STAT stat
    #define S_IFDIR _S_IFDIR
    #include <sys/stat.h>
    #define MKDIR(path) mkdir(path, 0777)
#endif


// max files that can be held at a time
#define MAX_BACKUPS 5

// creates backup files
void backupFile(const char *fileName);

// removes old backups if needed
void cleanupOldBackups(void);

// deletes old backups
void removeBackupFile(const char *fileName);

// takes the newest backup fiel and laods it
int loadInventoryFromBackupFile(void);

void checkBackupFiles(void);


bool directoryExists(const char *path);

#endif
