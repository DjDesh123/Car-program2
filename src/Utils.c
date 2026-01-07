#include <stdio.h>
#include "../include/Utils.h"



// Used for qsort() to sort backup files by last modified time (oldest first)
static int compareBackupTime(const void *a, const void *b) {
    const BackupFile *fileA = a;
    const BackupFile *fileB = b;
    return (fileA->modified_time < fileB->modified_time) ? -1 : 1;
}


int countBackupFiles(const char *dirPath) {
    size_t count =0;

#ifdef _WIN32
    WIN32_FIND_DATA findData;
    char searchPath[MAX_PATH];

    snprintf(searchPath, sizeof(searchPath), "%s\\*", dirPath);

    HANDLE hFind = FindFirstFile(searchPath, &findData);

    if (hFind == INVALID_HANDLE_VALUE) return 0;

    do {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            count++;
        }
    }while (FindNextFile(hFind, &findData) != 0);


    FindClose(hFind);

#else
    DIR *dir = opendir(dirPath);

    if (!dir) return 0;


    struct dirent *entry;

    while ((entry = readdir(dir)) !=  NULL ) {
        if (entry->d_type != DT_DIR) {
            count++;
        }
    }
    closedir(dir);



#endif
    return count;
}

void clearInputBuffer() {
    while (getchar() != '\n');
}
