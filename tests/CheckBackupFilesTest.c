#include <assert.h>
#include <stdbool.h>



// assumption variables
int backupCount = 0;
bool cleanUpOldBackupFiles = false;

#define MAX_BACKUPS  5

void cleanupOldBackups(void) {
    cleanUpOldBackupFiles = true;
}

int countBackUpFiles(const char *path) {
    (void)path; // silence unused warning
    return backupCount;
}

void checkBackupFiles(void) {
    if (countBackUpFiles("storage/backup") > MAX_BACKUPS) {
        cleanupOldBackups();
    }
}

int main(void) {
    //test 1: above the max backups
    backupCount=10;

    checkBackupFiles();
    assert(cleanUpOldBackupFiles == true);

    //test 2: under the max backups
    backupCount = 3;
    cleanUpOldBackupFiles = false;

    checkBackupFiles();
    assert(cleanUpOldBackupFiles == false);

    return 0;

}