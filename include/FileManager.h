#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H


#include <stdio.h>

// Creates a backup of the given file. Returns 0 on success, -1 on failure.
void backupFile(const char* fileName);
static void generateBackupFileName(const char* fileName,size_t size);


#endif // FILE_MANAGER_H
