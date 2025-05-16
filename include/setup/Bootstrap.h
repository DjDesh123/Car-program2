
#ifndef BOOTSTRAP_H
#define BOOTSTRAP_H


// function preprocessor
void initSystemStorage();
void createStorageFolder();
void createBackupFolder();
void checkInventoryFileExist();


// for windows
#ifdef _WIN32
    #define STAT _stat
    #define S_IFDIR _S_IFDIR
    #include <direct.h>
    #include <stdbool.h>
    #define MKDIR(path) _mkdir(path)
// for linux and apple
#else
    #define STAT stat
    #define S_IFDIR _S_IFDIR
    #include <sys/stat.h>
    #include <stdbool.h>
    #define MKDIR(path) mkdir(path, 0777)
#endif

// to check if the directory exists
bool directoryExists(const char *path) {
    struct STAT st;

    // Check if the given path exists and is a directory:
    // 1. Use stat() to get info about the path; returns 0 if successful.
    // 2. Check the file mode bits to see if it's flagged as a directory.
    // Returns true if both conditions are met, false otherwise.
    return (STAT(path, &st) == 0 && (st.st_mode & S_IFDIR));
}



#endif //BOOTSTRAP_H
