#include <inventory/Inventory.h>
#include <stdio.h>
#include <stdlib.h>

// add some notes with this
long getFileSize(const char *fileName) {

    // opened in rb because we want the raw bytes exactly the way they are stored on the disk and no newline translation (\r\n to \n)
    // meaning ftell() will now give an accurate byte count
    FILE *filePath = fopen(fileName, "rb");


    //moves the internal file pointer from the start to the end of the file
    fseek(filePath, 0, SEEK_END);

    long size = ftell(filePath);

    //releases OS resources
    fclose(filePath);
    return size;
}

//The main plan is use structs and dynamic arrays with dynamic memory to access this stuff so first i needf to create a header file and to put all this stuff in there
int createInventory() {
    printf("Creating Inventory...\n");

    // gets the size of the file
    long fileSize = getFileSize("storage/Inventory.dat");

    // to find the total number of records
    long inventorySize = fileSize/sizeof(car);

    // gets the dynamic size for the struct array

    //creates and populates the struct array carInventory
    car *carInventory= malloc(inventorySize*sizeof(car));
    FILE* inventoryFile = fopen("storage/Inventory.dat", "rb");

    // reads the items in binary forms
    size_t inventoryItems = fread(carInventory, sizeof(car), inventorySize, inventoryFile);

    fclose(inventoryFile);
}
