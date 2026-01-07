#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PATH_MAX 260

#ifdef _WIN32
    #include <windows.h>

#else
    #include <dirent.h>
    #include <sys/stat.h>
    #define DIR_HANDLE DIR*
    #define OPEN_DIR(path) opendir(path)
    #define CLOSE_DIR(handle) closedir(handle)
    #define FILE_STAT(path, buf) stat(path, buf)
    #define FILE_INFO struct stat
#endif

// Internal struct for tracking each backup's full path and last modified time
typedef struct {
    char path[256];            // Full path to back up file
    time_t modified_time;      // File's last modified time from system metadata
} BackupFile;



int countBackupFiles(const char *dirPath);
static int compareBackupTime(const void *a, const void *b);
void clearInputBuffer();

#endif //UTILS_H
