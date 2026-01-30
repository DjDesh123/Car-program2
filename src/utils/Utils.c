#include <stdio.h>
#include "utils/Utils.h"

#include <string.h>

#ifdef _WIN32
    #include <windows.h>

#else
    #include <unistd.h>
    #include <dirent.h>
    #include <sys/stat.h>
    #define DIR_HANDLE DIR*
    #define OPEN_DIR(path) opendir(path)
    #define CLOSE_DIR(handle) closedir(handle)
    #define FILE_STAT(path, buf) stat(path, buf)
    #define FILE_INFO struct stat
#endif

// Used for qsort() to sort backup files by last modified time (oldest first)
 int compareBackupTime(const void *a, const void *b) {
    const BackupFile *fileA = a;
    const BackupFile *fileB = b;
    return (fileA->modified_time < fileB->modified_time) ? -1 : 1;
}

int countBackupFiles(const char *dirPath) {
    size_t count = 0;

#ifdef _WIN32
    WIN32_FIND_DATA findData;
    char searchPath[PATH_MAX];

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

// size is going to be the countBackupFiles
// then create the array to then use a qsort
char** createFileNameArray(int size,const char *dirPath) {
    size_t count = 0;

    // allocates the space for pointer to filenames
    char **array = malloc(size * sizeof *array);

    if (!array) {
        return NULL;
    }

    #ifdef _WIN32
        WIN32_FIND_DATA findData;
        char searchPath[MAX_PATH];

        //stored in the buffer
        snprintf(searchPath, sizeof(searchPath), "%s\\*", dirPath);

        HANDLE hFind = FindFirstFile(searchPath, &findData);

        if (hFind == INVALID_HANDLE_VALUE) {
            free(array);
            return NULL;
        }

        do {
            //guard statement
            if (count >= size) break;

            // skips directories
            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {

                // allocates memory for this filename (+1 for '\0')
                array[count] = malloc(strlen(findData.cFileName) + 1);

                //copy filename into our own memory
                strcpy(array[count], findData.cFileName);

                count++;
            }
        }while (FindNextFile(hFind, &findData) != 0);


        FindClose(hFind);
    // need to do this end as well
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
    return array;
}