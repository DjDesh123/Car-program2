
#ifndef BOOTSTRAP_H
#define BOOTSTRAP_H

#include <stdbool.h>


// function preprocessor
void initSystemStorage();
int createStorageFolder();
void createBackupFolder();
void checkInventoryFileExist();
bool directoryExists(const char *path);



// for windows
#ifdef _WIN32
    #define STAT _stat
    #define S_IFDIR _S_IFDIR
    #include <direct.h>
    #define MKDIR(path) _mkdir(path)
// for linux and apple
#else
    #define STAT stat
    #define S_IFDIR _S_IFDIR
    #include <sys/stat.h>
    #define MKDIR(path) mkdir(path, 0777)
#endif




#endif //BOOTSTRAP_H
