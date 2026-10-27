#include "utils/FileManager.h"
#include "inventory/Inventory.h"
#include "utils/Utils.h"

#include <stdlib.h>
#include <time.h>

#define BUFFER_SIZE 1024
#define TIMESTAMP_MAX 32
#define CHARACTER_MAX 256

#define BACKUP_PREFIX "backup_"
#define BACKUP_EXT ".dat"

#define BACKUP_DIR "./storage/backup"

#ifdef _WIN32
    #define MKDIR(path) _mkdir(path)
    #define PATH_SEP '\\'
#else
    #include <dirent.h>
    #include <sys/stat.h>
    #include <unistd.h>

    #define MKDIR(path) mkdir(path, 0777)
    #define PATH_SEP '/'
#endif

static bool checkInventoryFileExist();
static int countBackupFiles(const char *dirPath);






// find recent backup
void findRecentBackup(){
    // first see if theres any backups files
    // we need to make an array of the file paths 
    //then apply a sorting algorithm to find the most recent backup
}













// this function does multiple things what I can do is create a sub function and just call that which then will also handle all the other function calls that are needed to amke it work
static bool checkInventoryFileExist() {
  
  // creates a pointer to the file and puts it in read binary mode for efficiency
  FILE *file = fopen("storage/Inventory.dat", "rb");

  // checks if the file exist
  if (file) {
    //The scenario the file exist
    printf("File already exists.\n");
    fclose(file);
    return true;
  }
  fclose(file);
  return false;
}

static bool directoryExists(const char *path) {
    struct STAT st;

    // Check if the given path exists and is a directory:
    // 1. Use stat() to get info about the path; returns 0 if successful.
    // 2. Check the file mode bits to see if it's flagged as a directory.
    // Returns true if both conditions are met, false otherwise.
    return (STAT(path, &st) == 0 && (st.st_mode & S_IFDIR));
}

// creates the first main storage folder
bool createStorageFolder() {

  // checks if the file already exist
  if (directoryExists("storage")) {
    return true;
  }

  // if MKDIR is 0 then the file opened properly
  if (MKDIR("storage") != 0) {
    perror("Failed to create the storage directory");
    return false;
  }

  printf("creating folder....\n");
  return true;
}

// creates the backup folder
bool createBackupFolder() {

  if (directoryExists("storage/backup")) {
    printf("backup directory already exist\n");
    return true;
  }

  if (MKDIR("storage/backup") != 0) {
    perror("Failed to create the backup directory");
    return false;
  }

  printf("creating folder....\n");

  return true;
}

static int countBackupFiles(const char *dirPath) {
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


// checks and redirects if the backups exceed 5
void checkBackupFiles(void) {
    if (countBackupFiles("storage/backup") > MAX_BACKUPS){
        cleanupOldBackups();
    }
}


void cleanupOldBackups(void) {

    size_t count = countBackupFiles("storage/backup");

    if (count < MAX_BACKUPS) {
        return;
    }

    char **files = createFileNameArray(count,BACKUP_DIR);

    if (!files) {
        return;
    }

    // sorts backups from oldest to newest
    qsort(files,count,sizeof(char *),compareBackupTime);


    char fullPath[CHARACTER_MAX];

    // Build full path safely using a fixed-size buffer.
    // snprintf is used to prevent buffer overflows when filenames are longer than expected.
    snprintf(fullPath,sizeof(fullPath),"%s%c%s",BACKUP_DIR,PATH_SEP,BACKUP_DIR,files[0]);

    removeBackupFile(fullPath);

    // frees all the pointers from the char**
    for (size_t i = 0; i < count; i++) {
        free(files[i]);
    }
}

// Generates a unique backup filename with timestamp (e.g. backup_20250614_180000.dat)
static void generateBackupFileName(char *fileName, const int size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestamp[TIMESTAMP_MAX];

    // formats the timestamp
    strftime(timestamp, size, "%Y%m%d_%H%M%S.dat", t);

    // composes full backup filename with using the macros for path and naming
    snprintf(fileName,sizeof(timestamp),"%s%c%s%s%s",BACKUP_DIR,PATH_SEP,BACKUP_PREFIX,timestamp,BACKUP_EXT);
}

// Full flow to create a backup of a file and clean old ones first
void backupFile(const char* fileName) {
// this needs to be the check first which can be in a seperate function and can be called

    cleanupOldBackups(); // Always clean before adding a new one

    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        perror("Error opening source file");
        return;
    }

    char backupFileName[CHARACTER_MAX];
    generateBackupFileName(backupFileName, sizeof(backupFileName));

    FILE *backupFile = fopen(backupFileName, "wb");
    if (backupFile == NULL) {
        printf("Error opening backup file: %s\n", *compareBackupTime);
        fclose(file);
        return;
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        fwrite(buffer, 1, bytesRead, backupFile);
    }

    fclose(file);
    fclose(backupFile);
    printf("Backup created: %s\n", backupFileName);
}

void removeBackupFile(const char* fileName) {
    if (remove(fileName) != 0) {
        perror("remove failed");
    }
}

// counts the inventory from a backup file 
bool loadInventoryFromBackupFile() {

    
    const size_t count = countBackupFiles("storage/backup");

    if (count < MAX_BACKUPS) {
        return false;
    }

    // dont need this
    char **files = createFileNameArray(count,BACKUP_DIR);

    if (!files) {
        perror("Error opening backup files");
        return false;
    }

    // sorts backups from oldest to newest
    qsort(files,count,sizeof(char *),compareBackupTime);


    char fullPath[CHARACTER_MAX];

    // Build full path safely using a fixed-size buffer.
    // snprintf is used to prevent buffer overflows when filenames are longer than expected.
    snprintf(fullPath,sizeof(fullPath),"%s%c%s",BACKUP_DIR,PATH_SEP,files[count-1]);

    // frees all the pointers from the char**
    for (size_t i = 0; i < count; i++) {
        free(files[i]);
    }

    long fileSize = getFileSize(fullPath);
    long inventorySize = fileSize/sizeof(car);


    car *carInventory = malloc(inventorySize*sizeof(car));
    FILE *inventoryFile = fopen(fullPath, "rb");

    if (inventoryFile == NULL) {
        perror("Error opening backup file");
    }

    // TODO: understand why this isn't being used and why i wrote it it in the first place
    size_t inventoryItems =fread(carInventory,sizeof(car),inventorySize,inventoryFile);

    fclose(inventoryFile);


}

