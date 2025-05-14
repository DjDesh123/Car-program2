//
// Created by Deshawn Johal on 14/05/2025.
//

#ifndef BOOTSTRAP_H
#define BOOTSTRAP_H

// function preprocessor
void createStorageFolder();
void createBackupFolder();

// for windows
#ifdef _WIN32
    #include <direct.h>
    #define MKDIR(path) _mkdir(path)
// for linux and apple
#else
    #include <sys/stat.h>
    #include <sys/types.h>
    #define MKDIR(path) mkdir(path, 0777)
#endif

#endif


#endif //BOOTSTRAP_H
