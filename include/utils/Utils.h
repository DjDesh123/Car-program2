#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

#define MAX_PATH 256


// Internal struct for tracking each backup's full path and last modified time
typedef struct {
    char path[MAX_PATH];
    time_t modified_time;
} BackupFile;



int countBackupFiles(const char *dirPath);
int compareBackupTime(const void *a, const void *b);
void clearInputBuffer();
char** createFileNameArray(int size,const char *dirPath);

#endif //UTILS_H
