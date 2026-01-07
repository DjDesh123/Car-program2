#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Max number of .dat backups allowed at once
#define MAX_BACKUPS 5

// Folder and file naming stuff for backups
#define BACKUP_PREFIX "backup_"
#define BACKUP_EXT ".dat"

#ifdef _WIN32
    #include <windows.h>
    #include <direct.h>AC
    #define BACKUP_DIR "C:\\MyApp\\backup"
    #define MKDIR(path) _mkdir(path)
    #define PATH_SEP '\\'
#else
    #include <dirent.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #define BACKUP_DIR "./storage/backup"
    #define MKDIR(path) mkdir(path, 0777)
    #define PATH_SEP '/'
#endif


// Creates a backup of the given file. Returns 0 on success, -1 on failure.
void backupFile(const char* fileName);
void cleanupOldBackups(void);



#endif // FILE_MANAGER_H
