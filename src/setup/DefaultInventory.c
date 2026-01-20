#include <stdio.h>
#include "../include/setup/DefaultInventory.h"

// creates the default inventory
extern car carInventory[INITIAL_INVENTORY_SIZE] = {
    {"Toyota", 2017, 2500.00, 10},
    {"Honda", 2019, 2200.00, 15},
    {"Ford", 2020, 3000.00, 8},
    {"BMW", 2018, 3500.00, 5},
    {"Chevrolet", 2021, 2800.00, 12},
    {"Audi", 2016, 4500.00, 3},
    {"Mercedes", 2022, 5000.00, 4},
    {"Nissan", 2017, 2400.00, 18},
    {"Hyundai", 2020, 2300.00, 20},
    {"Kia", 2021, 2600.00, 7}
};

void defaultInventory() {
    //writes the inventory into the .dat file
    //using .dat for performance as well as its stores structs more efficiently which is perfect for this case

    FILE *inventoryFile = fopen("storage/Inventory.dat", "wb");

    // loops through the struct array via the initial size as it the default storage currently
    // this also means that we can write in the file each car until we have no more cars to write
    for (int i = 0; i < INITIAL_INVENTORY_SIZE; i++) {
        fprintf(inventoryFile, "%s %d %f %d \n", carInventory[i].name,carInventory[i].year,carInventory[i].price,carInventory[i].stock);
    }

    fclose(inventoryFile);
}