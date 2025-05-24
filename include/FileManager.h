#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H


#include <stdio.h>

// Creates a backup of the given file. Returns 0 on success, -1 on failure.
void backupFile(const char* fileName, const char* backupFileName);

#endif // FILE_MANAGER_H
