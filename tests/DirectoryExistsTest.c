#include <assert.h>
#include <stdio.h>
#include "stdbool.h"
#include "../include/FileManager.h"



int main() {
    // Test 1: non-existent directory
    assert(directoryExists("no_such_dir") == false);

    // Test 2: directory exists
    MKDIR("test_dir");
    assert(directoryExists("test_dir") == true);

    // Test 3: file exists but is not directory
    FILE *f = fopen("test_file", "w");
    fclose(f);
    assert(directoryExists("test_file") == false);

    printf("directoryExists tests passed\n");

    return 0;
}