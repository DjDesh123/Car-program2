
#ifndef BOOTSTRAP_H
#define BOOTSTRAP_H

#include <stdbool.h>


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

// function preprocessor
void initSystemStorage();
static int createStorageFolder();
static int createBackupFolder();
static bool checkInventoryFileExist();
bool directoryExists(const char *path);

#endif //BOOTSTRAP_H
